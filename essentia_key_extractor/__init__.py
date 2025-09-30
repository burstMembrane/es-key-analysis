"""Essentia Key Extractor - Slim Python wrapper for musical key detection"""

from typing import TypedDict
import numpy as np
import numpy.typing as npt

try:
    from ._keyext import key_extractor, key_extractor_from_file
except ImportError as e:
    raise ImportError(
        f"Failed to import _keyext module. "
        f"Make sure the package is properly installed. Error: {e}"
    )


class KeyResult(TypedDict):
    """Result from key extraction"""
    key: str  # Musical key (A, Bb, B, C, C#, D, Eb, E, F, F#, G, Ab)
    scale: str  # Scale type ("major", "minor", or "majmin")
    strength: float  # Confidence of estimation (0-1)


def extract_key(
    audio: npt.NDArray[np.float32],
    sample_rate: float = 44100.0
) -> KeyResult:
    """
    Extract musical key from audio signal.

    Args:
        audio: Mono audio signal as float32 numpy array
        sample_rate: Sample rate in Hz (must be 44100.0)

    Returns:
        Dictionary with 'key', 'scale', and 'strength' fields

    Raises:
        RuntimeError: If audio is not mono, not float32, or sample rate is not 44100

    Example:
        >>> import numpy as np
        >>> from essentia_key_extractor import extract_key
        >>> audio = np.zeros(44100, dtype=np.float32)  # 1 second of silence
        >>> result = extract_key(audio, sample_rate=44100.0)
        >>> print(f"Key: {result['key']} {result['scale']}")
    """
    return key_extractor(audio, sample_rate)


def extract_key_from_file(filename: str) -> KeyResult:
    """
    Extract musical key from audio file.

    Automatically loads and resamples audio to 44.1kHz mono.

    Args:
        filename: Path to audio file (supports common formats via FFmpeg)

    Returns:
        Dictionary with 'key', 'scale', and 'strength' fields

    Example:
        >>> from essentia_key_extractor import extract_key_from_file
        >>> result = extract_key_from_file("song.mp3")
        >>> print(f"Key: {result['key']} {result['scale']} (confidence: {result['strength']:.2f})")
    """
    return key_extractor_from_file(filename)


__version__ = "0.1.0"
__all__ = ["extract_key", "extract_key_from_file", "KeyResult"]