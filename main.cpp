#include <iostream>
#include "misc.h"
#include "ImageLoader.h"
#include "Geometry.h"
#include "OutputData.h"
#include <chrono>

using namespace std;

class ImageDataIterator {
    //This one should allow to iterate over the full dataset (possibly in a tiled version)
    //OR POSSIBLY HERE IT IS A GOOD IDEA TO GO TO PLANE C and loop over an array the
    //Make two versions of the inner loops and see how they look like, and how they perform

    // SHOULD I APPLY corrections on loading data asynchronously, or on reconstruction???
};




void reconstruct_data(ExperimentalParameters exp, ReconstructionParameters par) {

    ImageLoader measured_frames(exp, par);
    OutputData out(par);


//    step_size_inv = 1.0 * (number_of_pixels - 1) / maxind / 2
//    step_size = 1.0/step_size_inv
//
//    to_index = lambda c: np.around(step_size_inv[:,np.newaxis]*(c+maxind[:,np.newaxis])).astype(np.int64)



//    unit_cell_vectors = np.dot(unit_cell_transform_matrix, unit_cell_vectors)
//
//    if reconstruct_in_orthonormal_basis:
//        [Q, _] = np.linalg.qr(unit_cell_vectors.T)
//        unit_cell_vectors = Q.T
//
//
//    metric_tensor = np.dot(unit_cell_vectors, unit_cell_vectors.T)
//    [_, normalized_metric_tensor] = cov2corr(metric_tensor)
//    transfrom_matrix = np.linalg.cholesky(np.linalg.inv(normalized_metric_tensor))




//    micro_oscillation_angle = oscillation_angle / microsteps
//
//    #Calculate h for frame number 0
//    h_starting = det2lab_xds(h, 0, **instrument_parameters)[0]
//
//    for frame_number in np.arange(first_image, last_image, image_increment):
//        print "reconstructing frame number ", frame_number
//
//        image = get_image(image_name(frame_number))
//        image = image[measured_pixels]
//        image = image / corrections * scale[frame_number-first_image]
//
//        for m in np.arange(0, microsteps):
//	    #Phi is with respect to phi at frame number 0
//            phi_minus_phi0=( (frame_number - 0.5) * microsteps + m + 0.5) * micro_oscillation_angle
//	    h_frame = np.dot(rotvec2mat(rotation_axis, -np.deg2rad(phi_minus_phi0)), h_starting)
//
//            fractional = np.dot(unit_cell_vectors, h_frame)
//            del h_frame
//            indices = to_index(fractional)
//            del fractional
//
//            accumulate_intensity(image, indices, rebinned_data, number_of_pixels_rebinned, number_of_pixels,
//                                 all_in_memory)


    const size_t Nx = measured_frames.nx();
    const size_t Ny = measured_frames.ny();

//    const microstep_type dNx = par.dNx();
//    const microstep_type dNy = par.dNy();
//    const microstep_type dNf = par.dNf();

    // Baseline implementation. Check performance without loop unrolling
    auto t1 = chrono::system_clock::now();

    while(measured_frames.load_next_frame()) {
        auto t2 = chrono::system_clock::now();
        auto dms = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
        cout << "it took " << dms.count() << " milliseconds\n";
        t1 = chrono::system_clock::now();

        cout << "loaded frame " << measured_frames.curernt_frame_no() << endl;

        for(size_t x=0; x<Nx; ++x )
            for(size_t y=0; y<Ny; ++y)
                if(measured_frames.should_reconstruct(x, y)) {
                    corrected_frame_dt I = measured_frames.current_frame(x, y);
                    // No microstepping in the baseline implementation
                    int indices[3];
                    get_index(exp, par, x, y, measured_frames.curernt_frame_no(), indices);
                    if(indices_within_bounds(par, indices)) {
                        out.rebinned_data_at(indices[0],indices[1],indices[2])+=I;
                        out.no_pixels_rebinned_at(indices[0],indices[1],indices[2])+=1;
                    }
                }
    }

    out.save_data(par.output_filename, par, exp);




//
//    // Performance critical inner reconstruction loop
//    // unrolled from triple loop into nine tiled loops
//    while(measured_frames.get_next_portion()) {
//        // Tiled x and y loops
//        for(size_t xt=0; xt<Nx; tx+=par.x_tile)
//            for(size_t yt=0; yt<Ny; ny+=par.y_tile) {
//                //Inner frame x and y loops
//                for(size_t frame_i=0, frame_no = measured_frames.portion_starting_frame();
//                    frame_i<measured_frames.n_frames();
//                    ++frame_i, ++frame_no) {
//
//                    for(size_t x=xt; x<min(xt+par.x_tile, measured_frames.nx()); ++x)
//                        for(size_t y=yt; yt<min(yt+par.y_tile, measured_frames.ny()); ++y)
//                            if (measured_frames.should_reconstruct(x,y,frame_i)) {
//                                //microstep loops
//                                corrected_frame_dt I = measured_frames.portion(x, y,frame_i)
//
//                                for
//                        }
//
//
//                }
//
//            }
//
//
//
//    }


//
//    if all_in_memory:
//        if output_filename is None:
//            result = {}
//        else:
//            result = output_file
//
//        result["rebinned_data"] = np.reshape(rebinned_data, number_of_pixels)
//        result["number_of_pixels_rebinned"] = np.reshape(number_of_pixels_rebinned, number_of_pixels)
//    else:
//        result = output_file
//

//
//    if output_filename is None:
//        return result
//    else:
//        result.close()
}





/*
 *
 * def correction_coefficients(h, instrument_parameters, medium, polarization_factor, polarization_plane_normal,
                            wavelength, wavevector):
    # % prepare corrections
    #[~,scattering_vector_mm,unit_scattering_vector]=det2lab_xds([x(:) y(:)],0,...
    #            starting_frame,starting_angle,oscillation_angle,...
    #            rotation_axis,...
    #            wavelength,wavevector,...
    #            NX,NY,pixelsize_x,pixelsize_y,...
    #            distance_to_detector,x_center,y_center,...
    #            detector_x,...
    #            detector_y,...
    #            detector_normal);
    [_, scattering_vector_mm, unit_scattering_vector] = det2lab_xds(h, 0, **instrument_parameters)
    #% air absorption correction
    #medium = 'Air';%provided externally can be Air of Helium
    #mu = air_absorption_coefficient(medium,wavelength);
    #air_absorption = exp(-mu*np.sqrt(sum(scattering_vector_mm.^2)));
    # air absorption correction
    mu = air_absorption_coefficient(medium, wavelength)
    air_absorption = np.exp(
        -mu * np.sqrt(np.sum(scattering_vector_mm ** 2, axis=0)))  #check along which dimension. should be of size
    #% Polarisation
    #polarization_factor = 1;%0.9887/(1+0.9887); %provided externally
    #polarization_plane_normal = [0 1 0]; %provided externally
    #
    #polarization_plane_normal = polarization_plane_normal/norm(polarization_plane_normal); % just in case
    #polarization_plane_other_comp = np.cross(polarization_plane_normal,wavevector');
    #polarization_plane_other_comp = polarization_plane_other_comp/norm(polarization_plane_other_comp);
    #polarization_correction = (1-polarization_factor)*(1-(polarization_plane_normal*unit_scattering_vector).^2)+...
    #                       polarization_factor*(1-(polarization_plane_other_comp*unit_scattering_vector).^2);
    polarization_plane_normal = np.array(polarization_plane_normal)
    polarization_plane_normal = polarization_plane_normal / np.linalg.norm(polarization_plane_normal)  # just in case
    polarization_plane_other_comp = np.cross(polarization_plane_normal, wavevector.T)
    polarization_plane_other_comp = polarization_plane_other_comp / np.linalg.norm(polarization_plane_other_comp)
    polarization_correction = (1 - polarization_factor) * (
        1 - np.dot(polarization_plane_normal, unit_scattering_vector) ** 2) + \
                              polarization_factor * (
                                  1 - np.dot(polarization_plane_other_comp, unit_scattering_vector) ** 2)
    #% solid angle correction
    #direct_beam_direction = wavevector'/norm(wavevector);
    #solid_angle_correction = (direct_beam_direction*unit_scattering_vector).^3;
    direct_beam_direction = wavevector.T / np.linalg.norm(wavevector)
    solid_angle_correction = np.dot(direct_beam_direction, unit_scattering_vector) ** 3
    #corrections = solid_angle_correction.*polarization_correction.*air_absorption;
    corrections = solid_angle_correction * polarization_correction * air_absorption
    #clear solid_angle_correction polarization_correction air_absorption scattering_vector_mm x y unit_scattering_vector
    #we will hide this until Dima
    #del solid_angle_correction, polarization_correction, air_absorption, scattering_vector_mm, unit_scattering_vector
    #if(exist('detector_efficiency_correction.mat','file'))
    #    load detector_efficiency_correction;
    #    corrections = corrections./detector_efficiency_correction(:)';
    #    clear detector_efficiency_correction;
    #end
    #
    #corrections = corrections(measured_pixels)';
    #
    # TODO: implement detector efficiency for Pilatus
    return corrections


# function [rebinned_data,number_of_pixels_rebinned,Tp,metric_tensor]=...
# reconstruct_data(filename_template,...
# last_image,...
# reconstruct_in_orthonormal_basis,...
# maxind,...
# number_of_pixels,...
# measured_pixels,...
# microsteps,...
#                     unit_cell_transform_matrix)
def reconstruct_data(filename_template,
                     first_image,
                     last_image,
                     maxind,
                     number_of_pixels,
                     reconstruct_in_orthonormal_basis=False,
                     measured_pixels=None,
                     microsteps=[1, 1, 1],
                     #on the angle also allows fractional values. for example 1 1 0.1 will only take every tenth frame
                     unit_cell_transform_matrix=np.eye(3),
                     polarization_plane_normal=[0, 1, 0],  #default for synchrotron
                     polarization_factor=1,  #0.5 for laboratory
                     medium='Air',  #'Air' or 'Helium
                     path_to_XPARM=".",
                     output_filename='reconstruction.h5',
                     size_of_cache=100,
                     all_in_memory=False,
                     override=False,
                     scale=None):

    def image_name(num):
        return filename_template % num  #test above


    def get_image(fname):
        return fabio.open(fname).data

    #TODO: check mar2000 and 2300 is done properly with respect to oversaturated reflections. Check what happens in other cases too

    if measured_pixels is None:
        measured_pixels = get_image(image_name(1)) >= 0

    #TODO: maybe add scale 'median' where scale is defined as a median of a frame divided by a median of a first frame?
    if scale is None:
        scale = np.ones(last_image-first_image+1)
    else:
        assert(len(scale)==last_image-first_image+1)

    if microsteps is None:
        microsteps = (1, 1, 1)

    assert 3 == len(microsteps), 'Microsteps should have three values: along x, y and phi.'

    incr_xy = np.array(microsteps)[0:2]
    assert np.all(np.mod(incr_xy, 1) == 0), 'microsteps in x and y direction should be integer'

    #TODO: microstepping is omitted in this version
    assert np.all(
        incr_xy == np.array([1, 1])), 'microsteps are not implemented atm'  #see next section and also down there
    if not np.all(incr_xy == np.array([1, 1])):
        def get_image(fname):
            np.kron(fabio.open(fname).data,
                 np.ones(incr_xy))  # TODO: remove the copypaste from the previous definition of get_image
        measured_pixels = 1 == np.kron(measured_pixels, np.ones(incr_xy))

    microsteps = microsteps[2]
    if microsteps < 1:
        image_increment = 1 / microsteps
        assert (np.mod(image_increment, 1) == 0)
        microsteps = 1
    else:
        image_increment = 1

    assert (3, 3) == np.shape(unit_cell_transform_matrix)

    # prepare hkl indices
    h = np.mgrid[1:np.size(measured_pixels, 1) + 1, 1:np.size(measured_pixels, 0) + 1].T
    h = h.reshape((np.size(h) / 2, 2))
    h = h[np.reshape(measured_pixels, (-1)), :]

    number_of_pixels = np.array(number_of_pixels)
    assert len(number_of_pixels) == 3

    maxind = np.array(maxind, dtype=np.float_)
    assert len(maxind) == 3

    step_size_inv = 1.0 * (number_of_pixels - 1) / maxind / 2
    step_size = 1.0/step_size_inv

    to_index = lambda c: np.around(step_size_inv[:,np.newaxis]*(c+maxind[:,np.newaxis])).astype(np.int64)

    if output_filename is not None:
        if os.path.exists(output_filename):
            if override:
                os.remove(output_filename)
            else:
                raise Exception('file ' + output_filename + ' already exists')
        output_file = create_h5py_with_large_cache(output_filename, size_of_cache)

    if all_in_memory:
        rebinned_data = np.zeros(np.prod(number_of_pixels),dtype=np.float_)
        number_of_pixels_rebinned = np.zeros(np.prod(number_of_pixels),dtype=np.int_)
    else:
        if output_filename is None:
            raise Exception("output filename shoud be provided")

        rebinned_data = output_file.create_dataset('rebinned_data', shape=number_of_pixels, dtype='float64',
                                                   chunks=True)
        number_of_pixels_rebinned = output_file.create_dataset('number_of_pixels_rebinned', shape=number_of_pixels,
                                                               dtype='int', chunks=True)

    #read_xparm
    instrument_parameters = read_XPARM(path_to_XPARM)

    unit_cell_vectors = instrument_parameters['unit_cell_vectors']
    starting_frame = instrument_parameters['starting_frame']
    starting_angle = instrument_parameters['starting_angle']
    rotation_axis = instrument_parameters['rotation_axis']
    wavevector = instrument_parameters['wavevector']
    wavelength = instrument_parameters['wavelength']
    oscillation_angle = instrument_parameters['oscillation_angle']

    #TODO: implement microstepping
    #%in case of microstepping
    #if exist('incr_xy','var')
    #    NX=NX*incr_xy(1);
    #    NY=NY*incr_xy(2);
    #    pixelsize_x=pixelsize_x/incr_xy(1);
    #    pixelsize_y=pixelsize_y/incr_xy(2);
    #    x_center=x_center*incr_xy(1);
    #    y_center=y_center*incr_xy(2);
    #end

    unit_cell_vectors = np.dot(unit_cell_transform_matrix, unit_cell_vectors)

    if reconstruct_in_orthonormal_basis:
        [Q, _] = np.linalg.qr(unit_cell_vectors.T)
        unit_cell_vectors = Q.T


    metric_tensor = np.dot(unit_cell_vectors, unit_cell_vectors.T)
    [_, normalized_metric_tensor] = cov2corr(metric_tensor)
    transfrom_matrix = np.linalg.cholesky(np.linalg.inv(normalized_metric_tensor))

    corrections = correction_coefficients(h, instrument_parameters, medium, polarization_factor,
                                          polarization_plane_normal, wavelength, wavevector)


    micro_oscillation_angle = oscillation_angle / microsteps

    #Calculate h for frame number 0
    h_starting = det2lab_xds(h, 0, **instrument_parameters)[0]

    for frame_number in np.arange(first_image, last_image, image_increment):
        print "reconstructing frame number ", frame_number

        image = get_image(image_name(frame_number))
        image = image[measured_pixels]
        image = image / corrections * scale[frame_number-first_image]

        for m in np.arange(0, microsteps):
	    #Phi is with respect to phi at frame number 0
            phi_minus_phi0=( (frame_number - 0.5) * microsteps + m + 0.5) * micro_oscillation_angle
	    h_frame = np.dot(rotvec2mat(rotation_axis, -np.deg2rad(phi_minus_phi0)), h_starting)

            fractional = np.dot(unit_cell_vectors, h_frame)
            del h_frame
            indices = to_index(fractional)
            del fractional

            accumulate_intensity(image, indices, rebinned_data, number_of_pixels_rebinned, number_of_pixels,
                                 all_in_memory)

    if all_in_memory:
        if output_filename is None:
            result = {}
        else:
            result = output_file

        result["rebinned_data"] = np.reshape(rebinned_data, number_of_pixels)
        result["number_of_pixels_rebinned"] = np.reshape(number_of_pixels_rebinned, number_of_pixels)
    else:
        result = output_file

    result['space_group_nr'] = instrument_parameters['space_group_nr']
    result['unit_cell'] = instrument_parameters['cell']
    result['maxind'] = maxind
    result['metric_tensor'] = metric_tensor
    result['number_of_pixels'] = number_of_pixels
    result['step_size'] = step_size
    result['is_direct'] = False

    if output_filename is None:
        return result
    else:
        result.close()

#todo: add lower limits, they are needed here
#todo: add string for file version
#todo: define stepsize rather than number of pixels
#todo: think of making the output nexus compatible

 */


int main() {
    ExperimentalParameters exp = load_xparm("/Users/arkadiy/ag/data/GdFe77Si13/xds/XPARM.XDS");
    ReconstructionParameters par {\
    "/Users/arkadiy/ag/data/GdFe77Si13/images/gfs1_2_?????.cbf",
    1, 3600,
    {501,501,501},
    {-5,-5,-5},
    {10./500,10./500,10./500},
    false,
    "test2.h5",
    true,
    100};

    reconstruct_data(exp,par);

    return 0;
}