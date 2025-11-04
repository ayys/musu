{
  description = "xpet is a small desktop pet for x11 written in c";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
    flakeutils.url = "github:numtide/flake-utils";
  };

  outputs =
    { self, nixpkgs, flakeutils }:
    flakeutils.lib.eachDefaultSystem (system:
      let pkgs = nixpkgs.legacyPackages.${system}; in
      {
        packages = rec {
          musu = pkgs.stdenv.mkDerivation {
            name = "xpet";
            src = ./.;
            buildInputs = with pkgs; [
              gcc
              xorg.libX11
              xorg.libXext
              xorg.libXpm
              xorg.libXft
              pkg-config
              fontconfig
              lohit-fonts.devanagari
              xlsfonts
            ];
            # Skip the configure phase as it's a simple 'make' build
            dontConfigure = true;
            buildPhase = ''
            make
            '';
            installPhase = ''
            TERMINFO="$out" make install DESTDIR="$out" PREFIX=""
            '';
          };
          default = musu;
        };
        apps = rec {
          musu = flakeutils.lib.mkApp { drv = self.packages.${system}.musu; };
          default = musu;
        };
      }
    );
}
