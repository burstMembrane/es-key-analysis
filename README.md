# Essentia Key Extractor

Slim Python wrapper exposing Essentia's KeyExtractor algorithm for musical key detection.

## Installation

```bash
pip install -e .
```

## Usage

### From audio array

```python
import numpy as np
from essentia_key_extractor import extract_key

# Load audio as mono float32 at 44.1kHz
audio = np.zeros(44100, dtype=np.float32)
result = extract_key(audio, sample_rate=44100.0)

print(f"Key: {result['key']} {result['scale']}")
print(f"Confidence: {result['strength']:.2f}")
```

### From audio file

```python
from essentia_key_extractor import extract_key_from_file

result = extract_key_from_file("song.mp3")
print(f"Key: {result['key']} {result['scale']} (confidence: {result['strength']:.2f})")
```

## Output

Returns a dictionary with:
- `key`: Musical key (A, Bb, B, C, C#, D, Eb, E, F, F#, G, Ab)
- `scale`: Scale type ("major", "minor", or "majmin")
- `strength`: Confidence of estimation (0-1)

## Build Requirements

- C++ compiler with C++14 support
- CMake 3.20+
- FFmpeg/libav libraries
- libsamplerate
- Eigen3 (automatically downloaded if not found)

## Architecture

This package provides a minimal pybind11 wrapper around Essentia's KeyExtractor algorithm, including only the necessary dependencies:

- Core Essentia infrastructure
- KeyExtractor algorithm pipeline:
  - FrameCutter
  - Windowing
  - Spectrum
  - SpectralPeaks
  - SpectralWhitening
  - HPCP (Harmonic Pitch Class Profile)
  - Key algorithm with multiple profile types

The package is optimized for size and performance, omitting unnecessary Essentia algorithms.