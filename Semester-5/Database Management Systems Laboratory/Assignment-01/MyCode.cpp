#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int TotalNumberOfRegions = 0;
int TotalNumberOfSalesman = 0;

class SaleInfo {
    public:
        int regionNo;
        int salesmanNo;
        int prodCode;
        int units;

        SaleInfo(): regionNo(0),salesmanNo(0),prodCode(0),units(0) {};
        SaleInfo(int r,int s,int p,int u): regionNo(r),salesmanNo(s),prodCode(p),units(u) {
            TotalNumberOfRegions = max(r,TotalNumberOfRegions);
            TotalNumberOfSalesman = max(s,TotalNumberOfSalesman);
        }
};

vector<SaleInfo> readData(string fileName) {
    vector<SaleInfo> v;

    ifstream file(fileName);
    string entry;

    getline(file,entry);     //Ignoring the column names

    while(getline(file,entry)) {
            stringstream stream(entry);

            vector<string> dataContent;
            string temp;
            
            while(getline(stream,temp,',')) {
                dataContent.push_back(temp);
            }

            SaleInfo s(stoi(dataContent[0]),stoi(dataContent[1]),stoi(dataContent[2]),stoi(dataContent[3]));
            v.push_back(s);
    }

    return v;
}

int priceFinder(int arr[][2],int l,int r,int ProdID) {
    if(r>=l) {
        int mid = l + (r-l)/2;

        if(arr[mid][0] == ProdID) return mid;
        else if(arr[mid][0] > ProdID) return priceFinder(arr,l,mid-1,ProdID);
        else return priceFinder(arr,mid+1,r,ProdID);
    }

    return -1;
}

int main() {
    int productInfo[8][2];
    vector<SaleInfo> database = readData("SaleDetail.txt");
    ofstream file("Output.txt");
    vector<vector<int>> salesByRegion(TotalNumberOfRegions+1,vector<int>(TotalNumberOfSalesman+1,0));

    cout << "Give the unit price of Product 61: ";
    cin >> productInfo[0][1];
    cout << "Give the unit price of Product 63: ";
    cin >> productInfo[1][1];
    cout << "Give the unit price of Product 64: ";
    cin >> productInfo[2][1];
    cout << "Give the unit price of Product 65: ";
    cin >> productInfo[3][1];
    cout << "Give the unit price of Product 95: ";
    cin >> productInfo[4][1];
    cout << "Give the unit price of Product 97: ";
    cin >> productInfo[5][1];
    cout << "Give the unit price of Product 98: ";
    cin >> productInfo[6][1];
    cout << "Give the unit price of Product 99: ";
    cin >> productInfo[7][1];

    productInfo[0][0] = 61;
    productInfo[1][0] = 63;
    productInfo[2][0] = 64;
    productInfo[3][0] = 65;
    productInfo[4][0] = 95;
    productInfo[5][0] = 97;
    productInfo[6][0] = 98;
    productInfo[7][0] = 99;

    for(auto element : database) {
        int a = productInfo[priceFinder(productInfo,0,7,element.prodCode)][1];
        salesByRegion[element.regionNo][element.salesmanNo] += element.units*a;
    }

    file << setw(21) << "ABC Company";
    for(int i=1;i<=TotalNumberOfRegions;i++) {
        file << endl << endl << endl << "Region " << i << endl;
        file << "------------" << endl; 

        int totalSalebyRegion = 0;
        for(int j=1;j<=TotalNumberOfSalesman;j++) {
            file << "Salesman " << j << "\t\t\t Rs " << salesByRegion[i][j] << endl; 
            totalSalebyRegion += salesByRegion[i][j];
        }
        file << endl << "Total Sales at Region " << i << " : Rs " << totalSalebyRegion << endl;
    }

    return 0;
}