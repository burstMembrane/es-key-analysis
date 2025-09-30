#include "key_runner.h"
#include "vendor/essentia/src/essentia/essentia.h"
#include "vendor/essentia/src/essentia/algorithmfactory.h"
#include "vendor/essentia/src/essentia/streaming/algorithms/poolstorage.h"
#include "vendor/essentia/src/essentia/streaming/algorithms/vectorinput.h"
#include "vendor/essentia/src/essentia/scheduler/network.h"

using namespace std;
using namespace essentia;
using namespace essentia::streaming;
using namespace essentia::scheduler;

// Global initialization - only happens once per process
static bool essentia_initialized = false;
static void ensure_essentia_initialized() {
    if (!essentia_initialized) {
        essentia::init();
        essentia_initialized = true;
    }
}

KeyOut run_key_extractor(const float *mono_44100, size_t n_samples)
{
    ensure_essentia_initialized();
    KeyOut out;

    try {
        // Use standard algorithm approach (simpler for KeyExtractor)
        standard::AlgorithmFactory& factory = standard::AlgorithmFactory::instance();

        // Convert input to vector<Real>
        vector<Real> signal(mono_44100, mono_44100 + n_samples);

        // Create KeyExtractor algorithm
        standard::Algorithm* keyExtractor = factory.create("KeyExtractor");

        // Configure with default parameters (44.1kHz)
        keyExtractor->configure("sampleRate", 44100.0,
                               "frameSize", 4096,
                               "hopSize", 4096,
                               "profileType", "bgate");

        // Set up inputs and outputs
        string key;
        string scale;
        Real strength = 0.0;

        keyExtractor->input("audio").set(signal);
        keyExtractor->output("key").set(key);
        keyExtractor->output("scale").set(scale);
        keyExtractor->output("strength").set(strength);

        // Compute
        keyExtractor->compute();

        // Copy results to output structure
        out.key = key;
        out.scale = scale;
        out.strength = strength;

        // Clean up
        delete keyExtractor;

    }
    catch (const exception &e) {
        // Return empty results on error
        cerr << "KeyExtractor error: " << e.what() << endl;
        out.key = "";
        out.scale = "";
        out.strength = 0.0;
    }

    return out;
}

KeyOut run_key_extractor_from_file(const std::string& filename)
{
    ensure_essentia_initialized();
    KeyOut out;

    try {
        streaming::AlgorithmFactory& factory = streaming::AlgorithmFactory::instance();

        Pool pool;

        // Use MonoLoader to load audio file
        Algorithm* monoloader = factory.create("MonoLoader",
                                               "filename", filename,
                                               "sampleRate", 44100.0);

        // For key extraction, we need the whole file loaded first
        monoloader->output("audio") >> PC(pool, "audio");

        // Create and run network to load audio
        Network network(monoloader);
        network.run();

        // Get the loaded audio
        if (!pool.contains<vector<Real>>("audio")) {
            out.key = "";
            out.scale = "";
            out.strength = 0.0;
            return out;
        }

        vector<Real> signal = pool.value<vector<Real>>("audio");

        // Now use standard KeyExtractor algorithm
        standard::AlgorithmFactory& stdFactory = standard::AlgorithmFactory::instance();
        standard::Algorithm* keyExtractor = stdFactory.create("KeyExtractor");

        keyExtractor->configure("sampleRate", 44100.0,
                               "frameSize", 4096,
                               "hopSize", 4096,
                               "profileType", "bgate");

        string key;
        string scale;
        Real strength = 0.0;

        keyExtractor->input("audio").set(signal);
        keyExtractor->output("key").set(key);
        keyExtractor->output("scale").set(scale);
        keyExtractor->output("strength").set(strength);

        keyExtractor->compute();

        // Copy results to output structure
        out.key = key;
        out.scale = scale;
        out.strength = strength;

        delete keyExtractor;

    }
    catch (const exception &e) {
        cerr << "KeyExtractor from file error: " << e.what() << endl;
        out.key = "";
        out.scale = "";
        out.strength = 0.0;
    }

    return out;
}