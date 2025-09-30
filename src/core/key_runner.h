#pragma once
#include <cstddef>
#include <vector>
#include <string>

struct KeyOut
{
  std::string key;        // e.g., "A", "Bb", "C#", "D", etc.
  std::string scale;      // "major", "minor", or "majmin"
  double strength = 0.0;  // confidence of key estimation (0-1)
};

/**
 * Run Essentia's KeyExtractor on mono 44.1kHz float PCM.
 * Extracts musical key and scale from audio signal.
 */
KeyOut run_key_extractor(const float *mono_44100, size_t n_samples);

/**
 * File-based version that uses Essentia's MonoLoader internally
 */
KeyOut run_key_extractor_from_file(const std::string& filename);