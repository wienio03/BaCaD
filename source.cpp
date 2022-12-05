//Wienczyslaw Wlodyga
#include <iostream>
bool LaplaceOptimalization(long long int tab[32][32], int side) {
    for (int i = 0; i < side; i++){
        for(int j = i + 1 ; j < side; j++){
            int temp=0;
            for(int k = 0; k < side; k++){
                if(tab[i][k]==tab[j][k])temp++;
                if (temp==side) return true;
            }
        }
    }
    return false;
}
int pow(int x){
    if(x%2==0)return 1;
    else return (-1);
}
bool IsInsideOctal(int p, int l, int v, int oP, int oL, int oV, int R){
    int oD=((oP-p)*(oP-p))+((oL-l)*(oL-l))+((oV-v)*(oV-v));
    if ((R*R)>=oD) return true;
    return false;
}
bool IsInsideTetrahedron(int p, int l, int v, int tP, int tL, int tV, int tetraSide){
    int x=(p-tP);
    int y=(l-tL);
    int z=(v-tV);
    if(x<0)x=(-1)*x;
    if(y<0)y=(-1)*y;
    if(z<0)z=(-1)*z;
    int wektor = x+y+z;
   if(wektor<=tetraSide)return true;
   return false;
}
void subMatrix(int tab[32][32][32], char lvp, int i, int side, long long int sub[32][32]){
    if(lvp=='p'){
        for(int n = 0; n < side; n++){
            for(int j = 0; j < side; j++){
                sub[n][j]=tab[i][n][j];
            }
        }
    }
    if(lvp=='l'){
        for(int n = 0; n < side; n++){
            for(int j = 0; j < side; j++){
                sub[n][j]=tab[n][i][j];
            }
        }
    }
    if(lvp=='v'){
        for(int n = 0; n < side; n++){
            for(int j = 0; j < side; j++){
                sub[n][j]=tab[n][j][i];
            }
        }
    }
}
long long int LaplaceMatrixDeterminant(long long int tab[32][32], int side){
    long long int det = 0;
    long long int SubMatrix[32][32];
    if (side==2) return tab[0][0]*tab[1][1]-tab[0][1]*tab[1][0];
    else if (side==3) return (tab[0][0]*tab[1][1]*tab[2][2])+(tab[0][1]*tab[1][2]*tab[2][0])+(tab[0][2]*tab[1][0]*tab[2][1])-(tab[2][0]*tab[1][1]*tab[0][2])-(tab[2][1]*tab[1][2]*tab[0][0])-(tab[2][2]*tab[1][0]*tab[0][1]);
    else if(LaplaceOptimalization(tab,side))return 0;
    else {
        for (int n = 0; n < side; n++){
            int subK = 0;
            for(int k = 1; k < side; k++){
                int subJ = 0;
                for(int j = 0; j < side; j++){
                    if (j==n) continue;
                    SubMatrix[subK][subJ]=tab[k][j];
                    subJ++;
                }
                subK++;
            }
            det = det+(pow(n)*tab[0][n]*LaplaceMatrixDeterminant(SubMatrix,side-1));
        }
    }
    return det;
}
const int maxLength = 32;
int main() {
    //cube
    int sideLength;
    char input;
    int cube[maxLength][maxLength][maxLength];
    //prostopadloscian
    int cVertexL;
    int cVertexV;
    int cVertexP;
    int cHeight;
    int cWidth;
    int cDepth;
    //zadany czworoscian
    int tVertexL;
    int tVertexV;
    int tVertexP;
    int tSide;
    //oktal
    int oVertexL;
    int oVertexV;
    int oVertexP;
    int radius;
    //wyznacznik
    char k;
    int dimension;
    //program
    std::cin >> sideLength;
    if(sideLength == 0 || sideLength > maxLength)return 0;
    if(sideLength%2==0) {
        if (sideLength > 0 && sideLength <= maxLength) {
            //uzupelnienie tablicy
            if (sideLength == 0) std::cin >> cube[0][0][0];
            for (int depth = 0; depth < sideLength; depth++) {
                for (int height = 0; height < sideLength; height++) {
                    for (int width = 0; width < sideLength; width++) {
                        std::cin >> cube[depth][height][width];
                    }
                }
            }
        }
        do {
            std::cin >> input;
            //Prostopadloscian
            if (input == 'C') {
                std::cin >> cVertexL >> cVertexV >> cVertexP >> cHeight >> cWidth >> cDepth;
                int sum = 0;
                int lEnd;
                int wEnd;
                int dEnd;
                if(cVertexL>sideLength)cVertexL=sideLength;
                if(cVertexV>sideLength)cVertexV=sideLength;
                if(cVertexP>sideLength)cVertexP=sideLength;
                if(cVertexL>=(sideLength/2)){
                    lEnd=cVertexL;
                    cVertexL-=cHeight;
                    cHeight=lEnd;
                }
                else cHeight=cVertexL+cHeight;
                if(cVertexV>=(sideLength/2)){
                    wEnd=cVertexV;
                    cVertexV-=cWidth;
                    cWidth=wEnd;
                }
                else cWidth=cVertexV+cWidth;
                if(cVertexP>=(sideLength/2)){
                    dEnd=cVertexP;
                    cVertexP-=cDepth;
                    cDepth=dEnd;
                }
                else cDepth=cVertexP+cDepth;
                if(cVertexL<0)cVertexL=0;
                if(cVertexP<0)cVertexP=0;
                if(cVertexV<0)cVertexV=0;
                //suma
                for (int x = cVertexP; x <= cDepth; x++) {
                    for (int y = cVertexL; y <= cHeight; y++) {
                        for (int z = cVertexV; z <= cWidth; z++) {
                            sum += cube[x][y][z];
                        }
                    }
                }
                std::cout << sum << std::endl;
            }
            //Oktal
            if (input == 'O') {
                std::cin >> oVertexL >> oVertexV >> oVertexP >> radius;
                int sum = 0;
                int temp1 = oVertexL;
                int temp2 = oVertexP;
                int temp3 = oVertexV;
                int oHeight = radius;
                int oDepth = radius;
                int oWidth = radius;
                int lOEnd;
                int wOEnd;
                int dOEnd;
                if (oVertexL > sideLength)oVertexL = sideLength;
                if (oVertexV > sideLength)oVertexV = sideLength;
                if (oVertexP > sideLength)oVertexP = sideLength;
                if (oVertexL >= (sideLength / 2)) {
                    lOEnd = oVertexL;
                    oVertexL -= oHeight;
                    oHeight = lOEnd;
                } else oHeight = oVertexL + oHeight;
                if (oVertexV >= (sideLength / 2)) {
                    wOEnd = oVertexV;
                    oVertexV -= oWidth;
                    oWidth = wOEnd;
                } else oWidth = oVertexV + oWidth;
                if (oVertexP >= (sideLength / 2)) {
                    dOEnd = oVertexP;
                    oVertexP -= oDepth;
                    oDepth = dOEnd;
                } else oDepth = oVertexP + oDepth;
                if (oVertexL < 0)oVertexL = 0;
                if (oVertexP < 0)oVertexP = 0;
                if (oVertexV < 0)oVertexV = 0;
                //suma
                for (int x = oVertexP; x <= oDepth; x++) {
                    for (int y = oVertexL; y <= oHeight; y++) {
                        for (int z = oVertexV; z <= oWidth; z++) {
                            if (IsInsideOctal(x, y, z, temp2, temp1, temp3, radius))sum += cube[x][y][z];
                        }
                    }
                }
                std::cout << sum << std::endl;
            }
            //Czworoscian
            if (input == 'T'){
                std::cin >> tVertexL >> tVertexV >> tVertexP >> tSide;
                int sum = 0;
                int temp1 = tVertexL;
                int temp2 = tVertexP;
                int temp3 = tVertexV;
                int tHeight = tSide;
                int tDepth = tSide;
                int tWidth = tSide;
                int lTEnd;
                int wTEnd;
                int dTEnd;
                if (tVertexL > sideLength)tVertexL = sideLength;
                if (tVertexV > sideLength)tVertexV = sideLength;
                if (tVertexP > sideLength)tVertexP = sideLength;
                if (tVertexL >= (sideLength / 2)) {
                    lTEnd = tVertexL;
                    tVertexL -= tHeight;
                    tHeight = lTEnd;
                } else tHeight = tVertexL + tHeight;
                if (tVertexV >= (sideLength / 2)) {
                    wTEnd = tVertexV;
                    tVertexV -= tWidth;
                    tWidth = wTEnd;
                } else tWidth = tVertexV + tWidth;
                if (tVertexP >= (sideLength / 2)) {
                    dTEnd = tVertexP;
                    tVertexP -= tDepth;
                    tDepth = dTEnd;
                } else tDepth = tVertexP + tDepth;
                if (tVertexL < 0)tVertexL = 0;
                if (tVertexP < 0)tVertexP = 0;
                if (tVertexV < 0)tVertexV = 0;
                //suma
                for (int x = tVertexP; x <= tDepth; x++) {
                    for (int y = tVertexL; y <= tHeight; y++) {
                        for (int z = tVertexV; z <= tWidth; z++) {
                            if(IsInsideTetrahedron(x,y,z,temp2,temp1,temp3,tSide)) sum += cube[x][y][z];
                        }
                    }
                }
                std::cout << sum << std::endl;
            }
            //Wyznacznik
            if (input == 'D'){
                long long int subM[32][32];
                long long int det;
                std::cin >> k >> dimension;
                subMatrix(cube,k,dimension,sideLength,subM);
                det = LaplaceMatrixDeterminant(subM,sideLength);
                std::cout << det << std::endl;
            }
        } while (input != 'E');
    }
    return 0;
}