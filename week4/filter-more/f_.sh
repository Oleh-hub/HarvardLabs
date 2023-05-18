# roi
# Makes grey, reflected, blur and edged files
# grey:
./filter -g images/yard.bmp      images/yard_grey.bmp
./filter -g images/courtyard.bmp images/courtyard_grey.bmp
./filter -g images/stadium.bmp   images/stadium_grey.bmp
./filter -g images/tower.bmp     images/tower_grey.bmp
# reflected:
./filter -r images/yard.bmp      images/yard_reflected.bmp
./filter -r images/courtyard.bmp images/courtyard_reflected.bmp
./filter -r images/stadium.bmp   images/stadium_reflected.bmp
./filter -r images/tower.bmp     images/tower_reflected.bmp
# blur:
./filter -b images/yard.bmp      images/yard_blur.bmp
./filter -b images/courtyard.bmp images/courtyard_blur.bmp
./filter -b images/stadium.bmp   images/stadium_blur.bmp
./filter -b images/tower.bmp     images/tower_blur.bmp
# edged:
./filter -e images/yard.bmp      images/yard_edged.bmp
./filter -e images/courtyard.bmp images/courtyard_edged.bmp
./filter -e images/stadium.bmp   images/stadium_edged.bmp
./filter -e images/tower.bmp     images/tower_edged.bmp

# open one of samle images and the created files with filters:
eog images/tower_edged.bmp
eog images/tower_blur.bmp
eog images/tower_reflected.bmp
eog images/tower_grey.bmp
eog images/tower.bmp

pwd
