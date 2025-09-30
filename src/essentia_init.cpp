#include "essentia/algorithmfactory.h"

// --- Standard Algorithms ---
#include "algorithms/standard/framecutter.h"
#include "algorithms/standard/windowing.h"
#include "algorithms/standard/fftk.h"
#include "algorithms/standard/ifftk.h"
#include "algorithms/standard/spectrum.h"
#include "algorithms/standard/noiseadder.h"
#include "algorithms/standard/peakdetection.h"

// --- Key Analysis Algorithms ---
#include "algorithms/extractor/keyextractor.h"
#include "algorithms/tonal/key.h"
#include "algorithms/spectral/hpcp.h"
#include "algorithms/spectral/spectralpeaks.h"
#include "algorithms/spectral/spectralwhitening.h"

// --- Complex Domain Algorithms ---
#include "algorithms/complex/cartesiantopolar.h"
#include "algorithms/complex/magnitude.h"

// --- IO Algorithms ---
#include "algorithms/io/audioloader.h"
#include "algorithms/io/monoloader.h"

// --- Standard Algorithms needed by MonoLoader ---
#include "algorithms/standard/monomixer.h"
#include "algorithms/standard/resample.h"

// --- Filters ---
#include "algorithms/filters/iir.h"

// Algorithm registration functions following Essentia's pattern
namespace essentia
{
  namespace standard
  {
    void registerAlgorithm()
    {
      AlgorithmFactory::Registrar<FrameCutter> regFrameCutter;
      AlgorithmFactory::Registrar<Windowing> regWindowing;
      AlgorithmFactory::Registrar<FFTK> regFFTK;
      AlgorithmFactory::Registrar<IFFTK> regIFFTK;
      AlgorithmFactory::Registrar<Spectrum> regSpectrum;
      AlgorithmFactory::Registrar<NoiseAdder> regNoiseAdder;
      AlgorithmFactory::Registrar<PeakDetection> regPeakDetection;
      AlgorithmFactory::Registrar<CartesianToPolar> regCartesianToPolar;
      AlgorithmFactory::Registrar<Magnitude> regMagnitude;
      AlgorithmFactory::Registrar<KeyExtractor> regKeyExtractor;
      AlgorithmFactory::Registrar<Key> regKey;
      AlgorithmFactory::Registrar<HPCP> regHPCP;
      AlgorithmFactory::Registrar<SpectralPeaks> regSpectralPeaks;
      AlgorithmFactory::Registrar<SpectralWhitening> regSpectralWhitening;
      AlgorithmFactory::Registrar<AudioLoader> regAudioLoader;
      AlgorithmFactory::Registrar<MonoLoader> regMonoLoader;
      AlgorithmFactory::Registrar<MonoMixer> regMonoMixer;
      AlgorithmFactory::Registrar<Resample> regResample;
      AlgorithmFactory::Registrar<IIR> regIIR;
    }
  }
  namespace streaming
  {
    void registerAlgorithm()
    {
      AlgorithmFactory::Registrar<FrameCutter, essentia::standard::FrameCutter> regFrameCutter;
      AlgorithmFactory::Registrar<Windowing, essentia::standard::Windowing> regWindowing;
      AlgorithmFactory::Registrar<FFTK, essentia::standard::FFTK> regFFTK;
      AlgorithmFactory::Registrar<CartesianToPolar, essentia::standard::CartesianToPolar> regCartesianToPolar;
      AlgorithmFactory::Registrar<KeyExtractor, essentia::standard::KeyExtractor> regKeyExtractor;
      AlgorithmFactory::Registrar<Key, essentia::standard::Key> regKey;
      AlgorithmFactory::Registrar<HPCP, essentia::standard::HPCP> regHPCP;
      AlgorithmFactory::Registrar<SpectralPeaks, essentia::standard::SpectralPeaks> regSpectralPeaks;
      AlgorithmFactory::Registrar<SpectralWhitening, essentia::standard::SpectralWhitening> regSpectralWhitening;
      AlgorithmFactory::Registrar<Spectrum, essentia::standard::Spectrum> regSpectrum;
      AlgorithmFactory::Registrar<Magnitude, essentia::standard::Magnitude> regMagnitude;
      AlgorithmFactory::Registrar<AudioLoader, essentia::standard::AudioLoader> regAudioLoader;
      AlgorithmFactory::Registrar<MonoLoader, essentia::standard::MonoLoader> regMonoLoader;
      AlgorithmFactory::Registrar<MonoMixer, essentia::standard::MonoMixer> regMonoMixer;
      AlgorithmFactory::Registrar<Resample, essentia::standard::Resample> regResample;
    }
  }
}