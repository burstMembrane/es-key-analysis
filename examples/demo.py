#!/usr/bin/env python3
"""Demo script for essentia-key-extractor"""

import argparse

from essentia_key_extractor import extract_key_from_file
from json import dumps

def main():
    parser = argparse.ArgumentParser(description="Extract musical key from audio file")
    parser.add_argument("audio_file", help="Path to audio file")
    args = parser.parse_args()
    result = extract_key_from_file(args.audio_file)
    print(dumps(result, indent=2))


if __name__ == "__main__":
    main()