# Meerkat2

Meerkat2 is a program for reconstructing reciprocal space from single-crystal diffraction measurements. It takes raw detector frames (CBF or HDF5 format) and an orientation matrix from [XDS](https://xds.mr.mpg.de/) (`XPARM.XDS`) and reconstructs them onto a regular grid in reciprocal space.

Pre-built binaries for Linux, Windows and macOS are available on the [Releases](../../releases) page.

## Usage

```
Meerkat2 configuration_file.mrk
```

Meerkat2 reads a single plain-text configuration file (conventionally `.mrk`). Lines starting with `#` or `!` are comments.

### Example configuration file

```
# reconstruct.mrk

DATA_FILE_TEMPLATE ../frames/sample_?????.cbf
XPARM_FILE ../XPARM.XDS
FIRST_FRAME 1
LAST_FRAME 3599
NUMBER_OF_PIXELS 601 601 601
LOWER_LIMITS -6 -6 -22
SYMMETRIC_LIMITS
POLARIZATION_PLANE_NORMAL 1 0 0
POLARIZATION_FACTOR 0.99
OUTPUT_FILENAME reconstruction.h5
MASK masks/mask.h5
```

### Configuration keywords

| Keyword | Arguments | Description                                                                                                                                                                              |
|---|---|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `DATA_FILE_TEMPLATE` | path | Path to raw frames. Replace the frame number with `?` characters, following the XDS convention.                                                                                          |
| `XPARM_FILE` | path | Path to `XPARM.XDS` or `GXPARM.XDS` with the crystal orientation matrix determined by XDS.                                                                                               |
| `FIRST_FRAME` | n | First frame number to reconstruct.                                                                                                                                                       |
| `LAST_FRAME` | n | Last frame number to reconstruct. If omitted, Meerkat2 scans forward from `FIRST_FRAME` and stops at the first missing file (up to frame 10000).                                        |
| `NUMBER_OF_PIXELS` | Nh Nk Nl | Number of voxels in the output grid along h, k, l. Should be odd.                                                                                                                        |
| `LOWER_LIMITS` | h k l | Minimum h, k, l values in the reconstructed volume. For 3D-∆PDF calculations, use integer values.                                                                                       |
| `UPPER_LIMITS` | h k l | Maximum h, k, l values. Alternatively, use `SYMMETRIC_LIMITS`.                                                                                                                           |
| `SYMMETRIC_LIMITS` | | Flag (no arguments). Sets the upper limits to the negated lower limits, making the grid symmetric around the origin. Required for FFT-based Fourier transform to the PDF map.            |
| `POLARIZATION_PLANE_NORMAL` | x y z | Direction of the polarisation plane normal in the XDS laboratory coordinate system.                                                                                                      |
| `POLARIZATION_FACTOR` | f | Polarization factor: 0.5 for X-ray tube, close to 1.0 for synchrotron radiation.                                                                                                         |
| `OUTPUT_FILENAME` | path | Output file name. The output is in HDF5-based Yell format (see below).                                                                                                                   |
| `MASK` | path | Path to an HDF5 mask file. Must contain a dataset `/data` with the same pixel dimensions as the detector: 1 = reconstruct, 0 = ignore. Use to mask hot pixels, beamstop, etc.            |
| `MICROSTEP_FRAMES` | n | Number of sub-steps per frame. Use n > 1 to reduce aliasing when rotation steps are coarse (e.g. 1 degree). Default: 1.                                                                  |
| `RECONSTRUCT_EVERY_NTH_FRAME` | n | Reconstruct every n-th frame and skip the rest. Speeds up calculation at a price of ignoring experimental data, useful for seeing reconstructions live during an experiment. Default: 1. |
| `DETECTOR` | name | Detector type (e.g. `Pilatus_Si`). Used for absorption correction. Default: no correction.                                                                                               |
| `DETECTOR_THICKNESS` | mm | Detector sensor thickness in mm. Used together with `DETECTOR` for absorption correction.                                                                                                |

## Output format (Yell)

Reconstructions are saved in the Yell file format, an HDF5-based format originally defined for the program Yell. These files can be used for calculation and refinement of the 3D-∆PDF.

Each file contains a 3D data array along with metadata:

| Dataset | Content |
|---|---|
| `format` | Format string (`"Yell 1.0"`) |
| `data` | 3D array of reconstructed intensities |
| `unit_cell` | Unit cell parameters (a, b, c, alpha, beta, gamma) |
| `step_sizes` | Grid step size along h, k, l |
| `lower_limits` | Coordinates of voxel `data[0,0,0]` |
| `is_direct` | `False` for diffuse scattering, `True` for PDF maps |

Yell files can be opened with any HDF5 library (Python/h5py, Matlab, C++, etc.).

### Visualisation

Reconstructed reciprocal space can be visualised with [DensityViewer](https://magnetcondensat.github.io/DensityViewer/) (available for Mac, Windows and Linux). General-purpose tools like Paraview can also open these files but will not display correct voxel aspect ratios.

## Building from source

Meerkat2 uses CMake and automatically downloads its dependencies (HDF5, Eigen, bitshuffle) during the build:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

On macOS, you can select the target architecture:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DTARGET_ARCH=arm64   # Apple Silicon
cmake -B build -DCMAKE_BUILD_TYPE=Release -DTARGET_ARCH=x86_64  # Intel
```

Requires CMake 3.24+ and a C++17 compiler.
