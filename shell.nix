{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    buildInputs = [
    pkgs.gnat13
    ];

    shellHook = ''
        echo "Configuring gcc inside nix-shell."
        export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.gcc.cc.lib}/lib"

        echo "Now inside Nix shell with environment ready!"
    '';
}
