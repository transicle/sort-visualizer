#!/usr/bin/env bash
set -e

echo "Detecting OS..."

install_macos() {
    echo "macOS detected"
    if ! command -v brew &>/dev/null; then
        echo "Homebrew not found. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    echo "Installing dependencies via Homebrew..."
    brew install ncurses sdl2 sdl2_mixer pkg-config
    echo ""
    echo "Note: On macOS, ncurses from Homebrew may need extra flags."
    echo "   If you get linker errors, try: export LDFLAGS=\"-L/opt/homebrew/opt/ncurses/lib\""
    echo "   and: export CPPFLAGS=\"-I/opt/homebrew/opt/ncurses/include\""
}

install_debian() {
    echo "Ubuntu/Debian detected"
    echo "Installing dependencies via apt..."
    sudo apt-get update -y --allow-unauthenticated 2>&1 | grep -v "^W:\|^N:" || true
    sudo apt-get install -y \
        build-essential \
        libncurses5-dev \
        libncursesw5-dev \
        libsdl2-dev \
        libsdl2-mixer-dev \
        pkg-config
}

install_fedora() {
    echo "Fedora/RHEL detected"
    echo "Installing dependencies via dnf..."
    sudo dnf install -y \
        gcc \
        make \
        ncurses-devel \
        SDL2-devel \
        SDL2_mixer-devel \
        pkg-config
}

install_arch() {
    echo "Arch Linux detected"
    echo "Installing dependencies via pacman..."
    sudo pacman -Sy --noconfirm \
        base-devel \
        ncurses \
        sdl2 \
        sdl2_mixer \
        pkg-config
}

case "$(uname -s)" in
    Darwin)
        install_macos
        ;;
    Linux)
        if [ -f /etc/os-release ]; then
            . /etc/os-release
            case "$ID" in
                ubuntu|debian|linuxmint|pop)
                    install_debian ;;
                fedora|rhel|centos|rocky|almalinux)
                    install_fedora ;;
                arch|manjaro|endeavouros)
                    install_arch ;;
                *)
                    echo "Unknown distro: $ID"
                    echo "Please install manually: ncurses, SDL2, SDL2_mixer, pkg-config"
                    exit 1 ;;
            esac
        else
            echo "Could not detect Linux distro (/etc/os-release missing)"
            exit 1
        fi
        ;;
    *)
        echo "Unsupported OS: $(uname -s)"
        exit 1
        ;;
esac

echo ""
echo "All dependencies installed. Run 'make' to build the project."