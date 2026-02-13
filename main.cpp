#include <iostream>
#include "misc.h"
//#include "ImageLoader.h"
#include "Geometry.h"
#include "OutputData.h"
#include "Corrections.h"
#include "AbstractImageLoader.h"
#include "ImageLoaderFactory.h"
#include <chrono>

//this might help with error messages when mmap memory allocation fails
//#if (defined(__MACH__) && defined(__APPLE__))
//#include <malloc/malloc.h>
//#elif defined(__linux__)
//#include <malloc.h>
//#endif

using namespace std;

class ImageDataIterator {
    //This one should allow to iterate over the full dataset (possibly in a tiled version)
    //OR POSSIBLY HERE IT IS A GOOD IDEA TO GO TO PLANE C and loop over an array the
    //Make two versions of the inner loops and see how they look like, and how they perform

    // SHOULD I APPLY corrections on loading data asynchronously, or on reconstruction???
};

// For the sake of possibility of future speed optimizations this function is written as close to C as possible
void reconstruct_data(ReconstructionParameters& par) {
    ExperimentalParameters & exp = par.exp;

    auto measured_frames = createImageLoader(par);
    measured_frames->load_mask(par.mask_filename);


    OutputData out(par);

    const size_t Nx = measured_frames->nx();
    const size_t Ny = measured_frames->ny();

    //Baseline implementation. Check performance without loop unrolling
    auto t1 = chrono::system_clock::now();

    Microstep ms_f(par.microsteps[2],par.frame_increment);

    //cache scattering vectors of each pixel without rotating
    vector<vec3>  scattering_vectors(Nx*Ny);
    vector<float> inv_corrections(Nx*Ny); //TODO: change to corrections, move inverse to the definition of the corrections function


    for(size_t x=0; x<Nx; ++x )
        for(size_t y=0; y<Ny; ++y) {
            scattering_vectors[x*Ny+y] = project_to_evald_sphere(exp, x, y);
            inv_corrections[x*Ny+y] = 1/calculate_correction_coefficient(exp, x, y);
        }

    for(int i=0; i<3; ++i) {
        par.inv_step_sizes[i] = 1/par.step_sizes[i];
    }

    while(measured_frames->load_next_frame()) {
        auto t2 = chrono::system_clock::now();
        auto dms = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

        cout << "loaded frame " << measured_frames->current_frame_no() << " in " << dms.count() << " milliseconds" << endl;

        t1 = chrono::system_clock::now();

        if(par.microsteps[2] == 1) //  should be kicking away frame microstepping and removing one indirection in the orientation matrix. Doesn't seem to add anything to the speed.
        {
            auto lab2hkl_mat = pixel_to_hkl_matrix(exp, measured_frames->current_frame_no());
            for(size_t ind=0; ind<Nx*Ny; ind+=1)
                    if(measured_frames->should_reconstruct(ind)) {
                        corrected_frame_dt I = measured_frames->current_frame(ind) * inv_corrections[ind];
                        {
                            int indices[3];
                            to_index(par,
                                     lab2hkl_mat*scattering_vectors[ind],
                                     indices);

                            if(indices_within_bounds(par, indices)) {
                                out.rebinned_data_at(indices[0],indices[1],indices[2]) += I;
                                out.no_pixels_rebinned_at(indices[0],indices[1],indices[2]) += 1;
                            }
                        }
                    }
        }
        else
        {
            vector<matrix_3x3> lab2hkl_mat;
            for(auto microstep_df=ms_f.start; microstep_df<ms_f.end; microstep_df+=ms_f.inc) {
                lab2hkl_mat.push_back(pixel_to_hkl_matrix(exp, measured_frames->current_frame_no()+microstep_df));
            }

            const size_t tile_size=4;
            for(size_t xt=0; xt<Nx; xt+=tile_size)
                for(size_t yt=0; yt<Ny; yt+=tile_size)
                    for(size_t x=xt; x<xt+tile_size && x<Nx; ++x )
                        for(size_t y=yt; y<yt+tile_size && y<Ny; ++y)
                            if(measured_frames->should_reconstruct(x, y)) {
                                corrected_frame_dt I = measured_frames->current_frame(x, y) * inv_corrections[x*Ny+y];
                                for(size_t microstep=0; microstep < ms_f.number; microstep += 1)
                                {
                                    int indices[3];
                                    //get_index(exp, par, x, y, measured_frames.curernt_frame_no(), indices);
                                    to_index(par,
                                             lab2hkl_mat[microstep]*scattering_vectors[x*Ny+y],
                                             indices);

                                    if(indices_within_bounds(par, indices)) {
                                        out.rebinned_data_at(indices[0],indices[1],indices[2])+=I;
                                        out.no_pixels_rebinned_at(indices[0],indices[1],indices[2])+=1;
                                    }
                                }

                            }
        }

    }

    cout << "Writing out " << par.output_filename << endl;
    out.save_data(par.output_filename, par);
}

//void reconstruct_data2(ExperimentalParameters & exp, ReconstructionParameters& par) {
//
//    ImageLoader measured_frames(par);
//    OutputData out(par);
//
//    const size_t Nx = measured_frames.nx();
//    const size_t Ny = measured_frames.ny();
//
//    // Baseline implementation. Check performance without loop unrolling
//    auto t1 = chrono::system_clock::now();
//
//    //cache scattering vectors of each pixel without rotating
//    vec3* scattering_vectors = (vec3*) malloc(sizeof(vec3)*Nx*Ny);
//
//    for(size_t x=0; x<Nx; ++x )
//        for(size_t y=0; y<Ny; ++y)
//            scattering_vectors[x*Ny+y] = project_to_evald_sphere(exp, x, y);
//
//    while(measured_frames.load_next_frame()) {
//        auto t2 = chrono::system_clock::now();
//        auto dms = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
//
//        cout << "loaded frame " << measured_frames.curernt_frame_no() << " in " << dms.count() << " milliseconds" << endl;
//
//        t1 = chrono::system_clock::now();
//
//        for(size_t x=0; x<Nx; ++x )
//            for(size_t y=0; y<Ny; ++y)
//                if(measured_frames.should_reconstruct(x, y)) {
//                    corrected_frame_dt I = measured_frames.current_frame(x, y);
//                    // No microstepping in the baseline implementation
//                    int indices[3];
//                    //get_index(exp, par, x, y, measured_frames.curernt_frame_no(), indices);
//                    to_index(par,
//                             exp.cell_vectors * rotate_to_frame(exp, scattering_vectors[x*Ny+y], measured_frames.curernt_frame_no()),
//                             indices);
//                    if(indices_within_bounds(par, indices)) {
//                        out.rebinned_data_at(indices[0],indices[1],indices[2])+=I;
//                        out.no_pixels_rebinned_at(indices[0],indices[1],indices[2])+=1;
//                    }
//                }
//    }
//
//
//    free(scattering_vectors);
//
//    cout << "Writing out " << par.output_filename << endl;
//    out.save_data(par.output_filename, par);
//}
//
//
//
//
//void reconstruct_data_baseline(ExperimentalParameters exp, ReconstructionParameters par) {
//
//    ImageLoader measured_frames(par);
//    OutputData out(par);
//
//
////    step_size_inv = 1.0 * (number_of_pixels - 1) / maxind / 2
////    step_size = 1.0/step_size_inv
////
////    to_index = lambda c: np.around(step_size_inv[:,np.newaxis]*(c+maxind[:,np.newaxis])).astype(np.int64)
//
//
//
////    unit_cell_vectors = np.dot(unit_cell_transform_matrix, unit_cell_vectors)
////
////    if reconstruct_in_orthonormal_basis:
////        [Q, _] = np.linalg.qr(unit_cell_vectors.T)
////        unit_cell_vectors = Q.T
////
////
////    metric_tensor = np.dot(unit_cell_vectors, unit_cell_vectors.T)
////    [_, normalized_metric_tensor] = cov2corr(metric_tensor)
////    transfrom_matrix = np.linalg.cholesky(np.linalg.inv(normalized_metric_tensor))
//
//
//
//
////    micro_oscillation_angle = oscillation_angle / microsteps
////
////    #Calculate h for frame number 0
////    h_starting = det2lab_xds(h, 0, **instrument_parameters)[0]
////
////    for frame_number in np.arange(first_image, last_image, image_increment):
////        print "reconstructing frame number ", frame_number
////
////        image = get_image(image_name(frame_number))
////        image = image[measured_pixels]
////        image = image / corrections * scale[frame_number-first_image]
////
////        for m in np.arange(0, microsteps):
////	    #Phi is with respect to phi at frame number 0
////            phi_minus_phi0=( (frame_number - 0.5) * microsteps + m + 0.5) * micro_oscillation_angle
////	    h_frame = np.dot(rotvec2mat(rotation_axis, -np.deg2rad(phi_minus_phi0)), h_starting)
////
////            fractional = np.dot(unit_cell_vectors, h_frame)
////            del h_frame
////            indices = to_index(fractional)
////            del fractional
////
////            accumulate_intensity(image, indices, rebinned_data, number_of_pixels_rebinned, number_of_pixels,
////                                 all_in_memory)
//
//
//    const size_t Nx = measured_frames.nx();
//    const size_t Ny = measured_frames.ny();
//
////    const microstep_type dNx = par.dNx();
////    const microstep_type dNy = par.dNy();
////    const microstep_type dNf = par.dNf();
//
//    // Baseline implementation. Check performance without loop unrolling
//    auto t1 = chrono::system_clock::now();
//
//    while(measured_frames.load_next_frame()) {
//        auto t2 = chrono::system_clock::now();
//        auto dms = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
//
//        cout << "loaded frame " << measured_frames.curernt_frame_no() << " in " << dms.count() << " milliseconds" << endl;
//
//        t1 = chrono::system_clock::now();
//
//        for(size_t x=0; x<Nx; ++x )
//            for(size_t y=0; y<Ny; ++y)
//                if(measured_frames.should_reconstruct(x, y)) {
//                    corrected_frame_dt I = measured_frames.current_frame(x, y);
//                    // No microstepping in the baseline implementation
//                    int indices[3];
//                    get_index(exp, par, x, y, measured_frames.curernt_frame_no(), indices);
//                    if(indices_within_bounds(par, indices)) {
//                        out.rebinned_data_at(indices[0],indices[1],indices[2])+=I;
//                        out.no_pixels_rebinned_at(indices[0],indices[1],indices[2])+=1;
//                    }
//                }
//    }
//
//
//    cout << "Writing out " << par.output_filename << endl;
//    out.save_data(par.output_filename, par);
//
//
////
////    // Performance critical inner reconstruction loop
////    // unrolled from triple loop into nine tiled loops
////    while(measured_frames.get_next_portion()) {
////        // Tiled x and y loops
////        for(size_t xt=0; xt<Nx; tx+=par.x_tile)
////            for(size_t yt=0; yt<Ny; ny+=par.y_tile) {
////                //Inner frame x and y loops
////                for(size_t frame_i=0, frame_no = measured_frames.portion_starting_frame();
////                    frame_i<measured_frames.n_frames();
////                    ++frame_i, ++frame_no) {
////
////                    for(size_t x=xt; x<min(xt+par.x_tile, measured_frames.nx()); ++x)
////                        for(size_t y=yt; yt<min(yt+par.y_tile, measured_frames.ny()); ++y)
////                            if (measured_frames.should_reconstruct(x,y,frame_i)) {
////                                //microstep loops
////                                corrected_frame_dt I = measured_frames.portion(x, y,frame_i)
////
////                                for
////                        }
////
////
////                }
////
////            }
////
////
////
////    }
//
//
////
////    if all_in_memory:
////        if output_filename is None:
////            result = {}
////        else:
////            result = output_file
////
////        result["rebinned_data"] = np.reshape(rebinned_data, number_of_pixels)
////        result["number_of_pixels_rebinned"] = np.reshape(number_of_pixels_rebinned, number_of_pixels)
////    else:
////        result = output_file
////
//
////
////    if output_filename is None:
////        return result
////    else:
////        result.close()
//}


///Quickly checks all required frames exist. If one does not thorows FileNotFound exception
void check_all_frames_exist(const ReconstructionParameters& par) {
    //TODO: move this check to abstract loader, since it is hard to figure out from hdf5 whether it is all good
    for(int i=par.first_image; i<=par.last_image; i+=par.frame_increment) {
        string filename = format_template(par.data_filename_template, i);
        if(!file_exists(filename))
            throw FileNotFound(filename);
    }
}


int main(int argc, char* argv[]) {
    if(argc < 2 || argc > 2) {
        cout << "usage: meerkat2 filename.mrk" << endl;
        return 0;
    }

    cout << "meerkat2 v. 0.38" << endl;

//this might help with error messages when mmap memory allocation fails
//#if (defined(__MACH__) && defined(__APPLE__))
//    mallopt(M_CHECK_ACTION, 0);
//#endif

    try {
        ReconstructionParameters par = load_refinement_parameters(argv[1]);

        cout << "Reconstructing frames: " << par.data_filename_template << endl;
        cout << "Using frames from " << par.first_image << " till " << par.last_image << endl;
        cout << "Output array name: " << par.output_filename << endl;
        cout << "Output array dimensions: " << par.number_of_pixels[0] << " " << par.number_of_pixels[1]
        << " " << par.number_of_pixels[2] << endl;
        cout << "In the limits ";
        for (int i=0; i<3; ++i)
            cout << par.lower_limits[i] << ' ' << par.lower_limits[i]+(par.number_of_pixels[i]-1)*par.step_sizes[i] << ' ';
        cout << endl << endl;

        load_xparm(par.xparm_filename, par.exp);

        cout << "Loaded experimental parameters" << endl;

        check_all_frames_exist(par);

        if(file_exists(par.output_filename)) {
            cout << "Warning: file \"" << par.output_filename << "\" will be overwritten" << endl;
        }

        cout << "Starting reconstruction" << endl << endl;

        reconstruct_data(par);

    }catch(const FileNotFound& f_err) {
        cout << "Error: file \"" << f_err.filename << "\" does not exist." << endl;
        return 0;
    } catch (const std::bad_alloc&) {
        cout  << endl << "Error: not enough operating memory." << endl;
        return 0;
//    } catch (const CBFError& e) {
//        cout << endl << "Error: file \"" << e.filename << "\" is not a valid cbf file. Use the program 2cbf from xds package to convert it to proper cbf format." << endl;
    } catch (const ParserError& e) {
        cout << e.description;
        return 0;
    } catch (const MaskError& e) {
        cout << e.description;
        return 0;
    }

    return 0;
}