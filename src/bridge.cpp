#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <numpy/ndarrayobject.h>
#include "core/key_runner.h"

namespace py = pybind11;

static inline void check_input(const py::array &x, double sr)
{
    if (x.ndim() != 1)
    {
        throw std::runtime_error("Expected mono 1D array, got " + std::to_string(x.ndim()) + "D array");
    }

    PyArrayObject *array = (PyArrayObject *)x.ptr();
    if (array->descr->type_num != NPY_FLOAT)
    {
        throw std::runtime_error("Expected float32 numpy array, got type_num=" + std::to_string(array->descr->type_num) + " (expected " + std::to_string(NPY_FLOAT) + ")");
    }

    if (sr != 44100.0)
    {
        throw std::runtime_error("Expected sample_rate=44100.0, got " + std::to_string(sr));
    }
}

py::dict key_extractor(py::array_t<float> x, double sample_rate)
{
    check_input(x, sample_rate);
    auto buf = x.request();
    auto *data = static_cast<float *>(buf.ptr);
    auto out = run_key_extractor(data, static_cast<size_t>(buf.size));

    py::dict d;
    d["key"] = out.key;
    d["scale"] = out.scale;
    d["strength"] = out.strength;
    return d;
}

py::dict key_extractor_from_file(const std::string& filename)
{
    auto out = run_key_extractor_from_file(filename);

    py::dict d;
    d["key"] = out.key;
    d["scale"] = out.scale;
    d["strength"] = out.strength;
    return d;
}

PYBIND11_MODULE(_keyext, m)
{
    m.doc() = "Essentia KeyExtractor (slim wrapper)";
    m.def("key_extractor", &key_extractor,
          py::arg("x"), py::arg("sample_rate"),
          "Extract key from audio array");
    m.def("key_extractor_from_file", &key_extractor_from_file,
          py::arg("filename"),
          "Extract key from audio file");
}