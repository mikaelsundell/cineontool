// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 - present Mikael Sundell.

#include <iostream>
#include <rawtoaces/image_converter.h>

RAWTOACES_USING_NAMESPACE

// openimageio
#include <OpenImageIO/argparse.h>
#include <OpenImageIO/filesystem.h>
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/sysutil.h>
#include <OpenImageIO/typedesc.h>

using namespace OIIO;

// prints
template<typename T>
static void
print_info(std::string param, const T& value = T())
{
    std::cout << "info: " << param << value << std::endl;
}

static void
print_info(std::string param)
{
    print_info<std::string>(param);
}

template<typename T>
static void
print_warning(std::string param, const T& value = T())
{
    std::cout << "warning: " << param << value << std::endl;
}

static void
print_warning(std::string param)
{
    print_warning<std::string>(param);
}

template<typename T>
static void
print_error(std::string param, const T& value = T())
{
    std::cerr << "error: " << param << value << std::endl;
}

static void
print_error(std::string param)
{
    print_error<std::string>(param);
}

// cineontool
struct Cineontool {
    bool help = false;
    bool verbose = false;
    std::string inputfilename;
    std::string outputfilename;
    int code = EXIT_SUCCESS;
};

static Cineontool tool;

static void
print_help(ArgParse& ap)
{
    ap.print_help();
}

int
main(int argc, const char* argv[])
{
    // Helpful for debugging to make sure that any crashes dump a stack
    // trace.
    Sysutil::setup_crash_stacktrace("stdout");

    // arguments
    std::vector<const char*> arguments;
    std::vector<std::string> iostrings;  // keep c_str() in scope
    if (argc == 2) {
        std::string inputfilename = argv[1];
        std::string output_extension = ".exr";
        std::string outputfilename = inputfilename;
        size_t last_dot = outputfilename.find_last_of(".");
        if (last_dot != std::string::npos) {
            outputfilename = outputfilename.substr(0, last_dot) + output_extension;
        }
        else {
            outputfilename += output_extension;
        }
        iostrings.push_back(inputfilename);
        iostrings.push_back(outputfilename);
        arguments = { argv[0], "--inputfilename", iostrings[0].c_str(), "--outputfilename",
                      iostrings[1].c_str() };
        argc = static_cast<int>(arguments.size());
    }
    else {
        for (int i = 0; i < argc; ++i) {
            arguments.push_back(argv[i]);
        }
    }

    Filesystem::convert_native_arguments(static_cast<int>(arguments.size()),
                                         (const char**)arguments.data());
    ArgParse ap;

    ap.intro("cineontool -- a utility for converting RAW scans to Cineon-encoded image\n");
    ap.usage("cineontool [options] filename...").add_help(false).exit_on_error(true);

    ap.separator("General flags:");
    ap.arg("--help", &tool.help).help("Print help message");

    ap.arg("-v", &tool.verbose).help("Verbose status messages");

    ap.separator("Input flags:");
    ap.arg("--inputfilename %s:INFILENAME", &tool.inputfilename)
        .help("Input filename of RAW negative");

    ap.separator("Output flags:");
    ap.arg("--outputfilename %s:OUTFILENAME", &tool.outputfilename)
        .help("Output filename of ACES exr");

    // clang-format on
    if (ap.parse_args(static_cast<int>(arguments.size()), (const char**)arguments.data()) < 0) {
        print_error("Could no parse arguments: ", ap.geterror());
        print_help(ap);
        ap.abort();
        return EXIT_FAILURE;
    }
    if (ap["help"].get<int>()) {
        print_help(ap);
        ap.abort();
        return EXIT_SUCCESS;
    }

    // cineontool program
    print_info("cineontool -- a utility for converting RAW scans to Cineon-encoded image");

    ImageConverter converter;

    return 0;
}
