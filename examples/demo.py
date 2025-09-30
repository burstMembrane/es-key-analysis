#!/usr/bin/env python3
"""Demo script for essentia-key-extractor"""

import argparse
import numpy as np
import soundfile as sf
import soxr

from essentia_key_extractor import extract_key, extract_key_from_file


def main():
    parser = argparse.ArgumentParser(description="Extract musical key from audio file")
    parser.add_argument("audio_file", help="Path to audio file")
    parser.add_argument("--method", choices=["manual", "auto"], default="auto",
                       help="Method: 'manual' loads/resamples audio, 'auto' uses from_file")
    args = parser.parse_args()

    if args.method == "auto":
        print(f"Method: from_file (automatic loading and resampling)")
        result = extract_key_from_file(args.audio_file)

    else:  # manual
        print(f"Method: manual (explicit loading and resampling)")

        # Load audio
        audio, sr = sf.read(args.audio_file, dtype='float32', always_2d=False)

        # Convert stereo to mono if needed
        if audio.ndim > 1:
            audio = audio.mean(axis=1)

        # Resample to 44.1kHz if needed
        if sr != 44100:
            print(f"Resampling from {sr}Hz to 44100Hz")
            audio = soxr.resample(audio, sr, 44100)

        # Extract key
        result = extract_key(audio, 44100.0)

    # Print results
    print(f"\nKey: {result['key']}")
    print(f"Scale: {result['scale']}")
    print(f"Confidence: {result['strength']:.3f}")


if __name__ == "__main__":
    main()