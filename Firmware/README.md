# Bluetooth LE Smart Lock - Firmware
Il s'agit du firmware à flasher dans le module BleuNRG.

# Comment compiler
1) Installer la chaîne de compilation croisé *arm-none-eabi-gcc*.
2) Installer l'outie *cmake*.
2) Télécharger le SDK [STSW-BLUENRG1-DK](https://www.st.com/en/embedded-software/stsw-bluenrg1-dk.html). Vous devrez vous inscrire sur ST.
3) Extrayez avec *innoextract* le contenu du dossier *library* vers `src/board/device/bluenrg-2`.
Par exemple, si vous avez téléchargé *STSW-BLUENRG1-DK* à proximité de README.md :
```
mkdir src/device/bluenrg-2
innoextract BlueNRG-1_2\ DK-3.2.3.0-Setup.exe -I app/Library
mv app/Library/* src/device/bluenrg-2/
rm -r app
```
4) Vous pouvez spécifier le répertoire de la chaîne d'outils avec la variable d'environnement *ARMGCC_DIR* si le complicateur croisé n'est pas trouvé.

5) Le model du module BlueNRG doit être passé à cmake via la variable *MODEL_BLUENRG* avec comme valeur soit *M2SA* ou *M2SP*. Par example pour compiler avec le BLUENRG-M2SA:
```
export ARMGCC_DIR="/to/directory/of/arm-gcc"
mkdir build
cd build
cmake --toolchain cmake/arm-none-eabi-gcc.cmake -DMODEL_BLUENRG=M2SA -DCMAKE_BUILD_TYPE=Release ..
make
```

# Comment flasher

## Via UART
1) Télécharger [RF-Flasher utility](https://www.st.com/en/embedded-software/stsw-bnrgflasher.html). Vous devrez vous inscrire sur ST.

## Via SWD
doto