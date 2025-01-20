from cli.build import build
from cli.config import config
from cli.install import install
import sys

def print_help():
        help_text = """
        Usage: rc.py [OPTIONS]

        Options:
          -c, --config  Configure the project
          -b, --build  Build the project
          -i, --install-arduino-cli  Install the executable
          -h, --help   Show this message and exit.
        """
        print(help_text)


def rc():
    """Command line interface for the rc_esp8266 project."""
    if '--help' in sys.argv or '-h' in sys.argv:
        print_help()
    if '--build' in sys.argv or '-b' in sys.argv:
        build.build_cmd()
    if '--config' in sys.argv or '-c' in sys.argv:
        config.config_cmd()
    if '--install-arduino-cli' in sys.argv or '-i' in sys.argv:
         install.install_cmd()

if __name__ == "__main__":
    rc()
    