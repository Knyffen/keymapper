
#include "Settings.h"
#include <cstdio>

bool interpret_commandline(Settings& settings, int argc, char* argv[]) {
  for (auto i = 1; i < argc; i++) {
    const auto argument = std::string(argv[i]);
    if (argument == "-u" || argument == "--update") {
      settings.auto_update_config = true;
    }
    else if (argument == "-c" || argument == "--config") {
      if (++i >= argc)
        return false;
      settings.config_file_path = argv[i];
    }
    else if (argument == "-v" || argument == "--verbose") {
      settings.verbose = true;
    }
    else if (argument == "--no-color") {
      settings.color = false;
    }
    else if (argument == "--check") {
      settings.check_config = true;
    }
    else {
      return false;
    }
  }
  return true;
}

void print_help_message(const char* argv0) {
  auto program = std::string(argv0);
  if (auto i = program.rfind('/'); i != std::string::npos)
    program = program.substr(i + 1);
  if (auto i = program.rfind('.'); i != std::string::npos)
    program = program.substr(0, i);

  const auto version =
#if __has_include("../../_version.h")
# include "../../_version.h"
  " ";
#else
  "";
#endif

  std::printf(
    "keymapper %s(c) 2019-2021 by Albert Kalchmair\n"
    "\n"
    "Usage: %s [-options]\n"
    "  -c, --config <path>  configuration file.\n"
    "  -u, --update         reload configuration file when it changes.\n"
    "  -v, --verbose        enable verbose output.\n"
    "  --no-color           no color on error output.\n"
    "  --check              check the config for errors.\n"
    "  -h, --help           print this help.\n"
    "\n"
    "All Rights Reserved.\n"
    "This program comes with absolutely no warranty.\n"
    "See the GNU General Public License, version 3 for details.\n"
    "\n", version, program.c_str());
}
