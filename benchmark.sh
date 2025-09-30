#!/bin/bash
CMD="python examples/demo.py test_60s.wav"

hyperfine --warmup 3 \
          --runs 10 \
          --export-markdown benchmark.md \
          "$CMD"
