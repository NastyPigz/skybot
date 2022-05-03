export $(cat .env | xargs)
{
    g++ -std=c++17 src/*.cpp -o bot -ldpp
} || {
    sudo apt-get install -y libopus0 libsodium23
    sudo dpkg -i /workspace/dpp-on-repl/libdpp-10.0.7-linux-x64.deb
    g++ -std=c++17 src/*.cpp -o bot -ldpp
}
./bot