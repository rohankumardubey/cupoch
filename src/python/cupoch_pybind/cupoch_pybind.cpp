#include "cupoch_pybind/cupoch_pybind.h"
#include "cupoch_pybind/camera/camera.h"
#include "cupoch_pybind/geometry/geometry.h"
#include "cupoch_pybind/io/io.h"
#include "cupoch_pybind/odometry/odometry.h"
#include "cupoch_pybind/registration/registration.h"
#include "cupoch_pybind/utility/utility.h"
#include "cupoch_pybind/visualization/visualization.h"

PYBIND11_MODULE(cupoch, m) {
    m.doc() = "CUDA-based 3D data processing library";

    py::enum_<rmmAllocationMode_t> rmm_mode(m, "AllocationMode",
                                            py::arithmetic());
     rmm_mode.value("CudaDefaultAllocation", CudaDefaultAllocation)
             .value("PoolAllocation", PoolAllocation)
             .value("CudaManagedMemory", CudaManagedMemory)
             .export_values();
    m.def("initialize_allocator", &cupoch::utility::InitializeAllocator,
          py::arg("mode") = CudaDefaultAllocation,
          py::arg("initial_pool_size") = 0,
          py::arg("logging") = false,
          py::arg("devices") = std::vector<int>());
    bind_device_vector_wrapper(m);
    pybind_utility(m);
    pybind_camera(m);
    pybind_geometry(m);
    pybind_io(m);
    pybind_registration(m);
    pybind_odometry(m);
    pybind_visualization(m);
}