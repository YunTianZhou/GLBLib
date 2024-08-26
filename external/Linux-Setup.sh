# Function to install packages using apt (for Debian/Ubuntu)
install_with_apt() {
    echo "Using apt to install dependencies..."
    sudo apt-get update
    sudo apt-get install -y libglfw3-dev libglew-dev libglm-dev libstb-dev
}

# Function to install packages using dnf (for Fedora)
install_with_dnf() {
    echo "Using dnf to install dependencies..."
    sudo dnf install -y glfw-devel glew-devel glm-devel stb-devel
}

# Function to install packages using yum (for CentOS/RHEL)
install_with_yum() {
    echo "Using yum to install dependencies..."
    sudo yum install -y glfw-devel glew-devel glm-devel stb-devel
}

# Function to install packages using pacman (for Arch Linux)
install_with_pacman() {
    echo "Using pacman to install dependencies..."
    sudo pacman -Sy --noconfirm glfw glew glm stb
}

# Detect the package manager and install dependencies
if [ -x "$(command -v apt-get)" ]; then
    install_with_apt
elif [ -x "$(command -v dnf)" ]; then
    install_with_dnf
elif [ -x "$(command -v yum)" ]; then
    install_with_yum
elif [ -x "$(command -v pacman)" ]; then
    install_with_pacman
else
    echo "Unsupported package manager. Please install the dependencies manually."
    exit 1
fi

echo "Setup successfully."

