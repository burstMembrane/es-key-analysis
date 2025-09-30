#!/usr/bin/env python3
"""Demo script for segmented key extraction"""

import argparse
from json import dumps
import soundfile as sf
import soxr
import numpy as np

from essentia_key_extractor import extract_key


def main():
    parser = argparse.ArgumentParser(description="Extract musical key from audio file using segmentation")
    parser.add_argument("audio_file", help="Path to audio file")
    parser.add_argument("-s","--segment-duration", type=float, default=30.0, help="Segment duration in seconds (default: 10.0)")
    args = parser.parse_args()

    # Load audio file
    audio, sr = sf.read(args.audio_file, dtype='float32', always_2d=False)

    # Convert stereo to mono if needed
    if audio.ndim > 1:
        audio = audio.mean(axis=1)

    # Resample to 44.1kHz if needed
    if sr != 44100:
        audio = soxr.resample(audio, sr, 44100)
        sr = 44100

    # Calculate segment size in samples
    segment_samples = int(args.segment_duration * sr)
    total_samples = len(audio)

    # Extract key for each segment
    segments = []
    for start in range(0, total_samples, segment_samples):
        end = min(start + segment_samples, total_samples)
        segment = audio[start:end]

        if len(segment) < sr:  # Skip segments shorter than 1 second
            continue

        result = extract_key(segment, sr)
        segments.append({
            "start_time": start / sr,
            "end_time": end / sr,
            "key": result["key"],
            "scale": result["scale"],
            "strength": result["strength"]
        })

    # Calculate average strength and most common key
    if segments:
        avg_strength = sum(s["strength"] for s in segments) / len(segments)

        # Count key+scale combinations
        key_counts = {}
        for s in segments:
            key_scale = f"{s['key']} {s['scale']}"
            key_counts[key_scale] = key_counts.get(key_scale, 0) + 1

        most_common = max(key_counts.items(), key=lambda x: x[1])
        most_common_key, most_common_scale = most_common[0].split()

        result = {
            "overall": {
                "key": most_common_key,
                "scale": most_common_scale,
                "avg_strength": avg_strength,
                "agreement": most_common[1] / len(segments)
            },
            "segments": segments
        }
    else:
        result = {"error": "No valid segments found"}

    print(dumps(result, indent=2))


if __name__ == "__main__":
    main()
