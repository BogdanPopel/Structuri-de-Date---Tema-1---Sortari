#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;

vector<unsigned long int> vec;
vector<unsigned long int> vecAUX;
vector<unsigned long int> Bubblevec;
vector<unsigned long int> Countvec;
vector<unsigned long int> CountvecAUX;
vector<unsigned long int> outputCOUNT;
vector<unsigned long int> Radixvec;
vector<unsigned long int> RadixvecAUX;
vector<unsigned long int> outputRADIX;
vector<unsigned long int> Radixvec16;
vector<unsigned long int> Radixvec256;
vector<unsigned long int> Mergevec;
vector<unsigned long int> Quickvec;
vector<unsigned long int> Insertvec;
vector<unsigned long int> Timvec;

unsigned long int T, N, MAX, RadixMAX;
const int subbArrSize = 32;


void generare_vector(unsigned long int SIZE, unsigned int long MAXIM, vector<unsigned long int>& arr)
{
    random_device device;

    mt19937_64 mersenne_engine{ device() };
    uniform_int_distribution<unsigned long int> RANGE{0, MAX};

    auto gen = [&RANGE, &mersenne_engine]()
    {
        return RANGE(mersenne_engine);
    };

    arr.resize(N);
    generate(arr.begin(), arr.end(), gen);
}

///--------------BUBBLE SORT------------------------------------------------------------------------------------------

void BubbleSort(vector<unsigned long int>& arr, unsigned long int N)
{
    if(N>100000)
    {
     cout<<"Bubble devine foarte incet de la 10^5 elemente. La 10^6 elemente spunem ca nu poate sorta."<< endl;
    return;
    }
    bool swapped = true;

    while(swapped)
    { swapped = false;
        for(int i = 0; i<arr.size()-1;i++)
        {
            if (arr[i] > arr[i+1])
            {
                arr[i] += arr[i+1];
                arr[i+1] = arr[i] - arr[i+1];
                arr[i] -= arr[i+1];
                swapped = true;
            }
        }

    }
}

///--------------COUNTING SORT------------------------------------------------------------------------------------------

CountSort(vector<unsigned long int>& arr)
{
    unsigned long int Max = *max_element(arr.begin(), arr.end());
    unsigned long int Min = *min_element(arr.begin(), arr.end());
    unsigned long int Range = Max - Min + 1;

    vector<unsigned long int> apparitions(Range);
    outputCOUNT.resize(arr.size(), 0);

    for(int i = 0; i < arr.size(); i++)
        apparitions[arr[i] - Min]++;

    for(int i = 1; i< apparitions.size(); i++)
        apparitions[i] += apparitions[i-1];

    for(int i = arr.size() - 1; i >= 0; i--)
    {
        outputCOUNT[apparitions[arr[i] - Min ] - 1] = arr[i];
        apparitions[arr[i] - Min]-- ;
    }

    for(int i = 0; i < arr.size(); i++)
        arr[i] = outputCOUNT[i];
}

///--------------RADIX SORT CLASSIC------------------------------------------------------------------------------------------

void RadixSort(vector<unsigned long int>& arr)
{
    int CUT = 1;
    RadixMAX = *(max_element(arr.begin(), arr.end()));

    while(RadixMAX/CUT)
    {
         vector<vector<unsigned long int>> Buckets(10, vector<unsigned long int>());

         for(auto termen : arr)
         {
             int cifra = termen / CUT % 10;
             Buckets[cifra].push_back(termen);
         }
         size_t k = 0;
         for(size_t i = 0; i<10; i++)
         {
             for(size_t j = 0; j < Buckets[i].size(); j++)
             {
                 arr[k] = Buckets[i][j];
                 k++;
             }
         }

        CUT *= 10;
    }
}

///--------------RADIX SORT BASE 16-------------------------------------------------------------------------------------------

void RadixSort16(vector<unsigned long int>& arr)
{
    int pos = 0;
    int Size = arr.size();
    vector<unsigned long int> outputRADIX16;
    outputRADIX16.resize(Size, 0);
    int Max = 1;

    while ( Max >> pos > 0)
    {
        vector<unsigned long int> apparitions(16, 0);

        for(auto termen : arr )
        {
            if (pos == 0)
            {
                if (termen > Max)
                    Max = termen;
            }
            apparitions[(termen >> pos) & 0xf]++;
        }

        for(int i = 1; i < 16; i++)
            apparitions[i] += apparitions[i-1];

        for(int i = Size-1; i >= 0; i-- )
        {
            int ElementCurent = (arr[i] >> pos) & 0xf;
            outputRADIX16[apparitions[ElementCurent] - 1] = arr[i];
            apparitions[ElementCurent]--;
        }

        arr.assign(outputRADIX16.begin(), outputRADIX16.end());
        pos += 4;
    }

}

///--------------RADIX SORT BASE 16-------------------------------------------------------------------------------------------

void RadixSort256(vector<unsigned long int>& arr)
{
    int pos = 0;
    int Size = arr.size();
    vector<unsigned long int> outputRADIX256;
    outputRADIX256.resize(Size, 0);
    int Max = 1;

    while ( Max >> pos > 0)
    {
        vector<unsigned long int> apparitions(256, 0);

        for(auto termen : arr )
        {
            if (pos == 0)
            {
                if (termen > Max)
                    Max = termen;
            }
            apparitions[(termen >> pos) & 0xff]++;
        }

        for(int i = 1; i < 256; i++)
            apparitions[i] += apparitions[i-1];

        for(int i = Size-1; i >= 0; i-- )
        {
            int ElementCurent = (arr[i] >> pos) & 0xff;
            outputRADIX256[apparitions[ElementCurent] - 1] = arr[i];
            apparitions[ElementCurent]--;
        }

        arr.assign(outputRADIX256.begin(), outputRADIX256.end());
        pos += 4;
    }

}



///--------------MERGE SORT-------------------------------------------------------------------------------------------

void MergeforMerge(vector<unsigned long int>& stanga, vector<unsigned long int>& dreapta, vector<unsigned long int>& arr)
{
    unsigned long int SizeStanga = stanga.size();
    unsigned long int SizeDreapta = dreapta.size();
    unsigned long int i = 0, j = 0, k = 0;
    while(j < SizeStanga && k < SizeDreapta)
    {
        if(stanga[j] < dreapta[k])
        {
            arr[i] = dreapta[j];
            j++;
        }
        else
        {
            arr[i] = dreapta[k];
            k++;
        }
        i++;
    }

    while(j < SizeStanga)
    {
        arr[i] = dreapta[j];
        j++;
        i++;
    }

    while(k < SizeDreapta)
    {
        arr[i] = dreapta[k];
        k++;
        i++;
    }
}

void MergeSort(vector<unsigned long int>& arr)
{
    if(arr.size() <= 1) return;


    if(arr.size() > 1000000)
        {
            cout<<"Merge nu sorteaza de la 10^6 elemente im sus.";
            return;
        }

    unsigned long int Middle = arr.size() / 2;
    vector<unsigned long int>MergevecLEFT;
    vector<unsigned long int>MergevecRIGHT;

    for(size_t i = 0; i < Middle; i++)
        MergevecLEFT.push_back(arr[i]);
    for(size_t i = 0; i < (arr.size()) - Middle; i++ )
        MergevecRIGHT.push_back(arr[Middle+i]);

    MergeSort(MergevecLEFT);
    MergeSort(MergevecRIGHT);
    MergeforMerge(MergevecLEFT, MergevecRIGHT, arr);

}

///--------------QUICK SORT-------------------------------------------------------------------------------------------

int Partitie(vector<unsigned long int>& arr,unsigned long int stanga,unsigned long int dreapta)
{

    unsigned long int PivotInd = stanga + (dreapta-stanga) / 2;
    unsigned long int Pivot = arr[PivotInd];
    int i = stanga, j = dreapta;
    unsigned long int temp;

    while(i <= j)
    {
        while(arr[i]<Pivot)
          {
             i++;
          }
        while(arr[j] > Pivot)
           {
             j--;
           }
        if(i <= j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void QuickSort(vector<unsigned long int>& arr, unsigned long int stanga, unsigned long int dreapta)
{
    if(stanga < dreapta)
    {
        unsigned long int PivotInd= Partitie(arr, stanga, dreapta);
        QuickSort(arr, stanga, PivotInd-1);
        QuickSort(arr, PivotInd, dreapta);
    }
}

///--------------INSERTION SORT-------------------------------------------------------------------------------------------

void InsertionSort(vector<unsigned long int>& arr)
{
    int i, j, Pivot, n;
    n = arr.size();
    if(n>100000)
    {
        cout<<"Insertion Sort devine foarte incet cand lucram cu multe elemente. la 10^6 elemente spunem ca nu poate sorta."<<endl;
        return;
    }

    for(i = 1; i < n; i++)
    {
        Pivot = arr[i];
        j = i-1;

        while( j >= 0 && arr[j] > Pivot)
        {
            arr[j+1] = arr[j];
            j-=1;
        }
        arr[j+1] = Pivot;
    }
}

///--------------TIM SORT-------------------------------------------------------------------------------------------

void InsertionForTIM(vector<unsigned long int>& arr, int stanga, int dreapta)
{

    for(int i = stanga + 1; i <= dreapta; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while( j >= stanga && arr[j] > temp)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

void Merge(vector<unsigned long int>& arr, int stanga, int mij, int dreapta)
{
    int Size1 = mij - stanga + 1, Size2 = dreapta - mij;
    vector<unsigned long int> Left;
    vector<unsigned long int> Right;

    for(int i = 0; i < Size1; i++)
        Left.push_back(arr[stanga + i]);
    for(int i = 0; i < Size2; i++)
        Right.push_back(arr[mij + 1 + i]);

    int i=0, j=0, k=stanga;

    while(i < Size1 && j < Size2)
    {
        if(Left[i] <= Right[j])
        {
            arr[k] = Left[i];
            i++;
        }
        else
        {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < Size1)
    {
        arr[k] = Left[i];
        k++;
        i++;

    }

    while(j < Size2)
    {
        arr[k] = Right[j];
        k++;
        j++;

    }
}

void TimSort(vector<unsigned long int>& arr)
{   int n = arr.size();
    if(n > 100000)
    {
        cout<<"TimSort nu sorteaza"<<endl;
        return;
    }

    for(int i = 0; i < n; i+= subbArrSize)
        InsertionForTIM(arr, i, min((i+31), (n-1)));

    for(int Size = subbArrSize; Size<n; Size = 2*Size)
    {
        for(int stanga = 0; stanga < n; stanga += 2*Size)
        {
            int mij = stanga + Size - 1;
            int dreapta = min((stanga + 2*Size - 1), (n-1));
            Merge(arr, stanga, mij, dreapta);
        }
    }
}

bool test_sort(vector<unsigned long int>& arr)
{
    bool e_ok = 1;
    for(int i = 1; i < arr.size()-1; i++)
    {
        if(arr[i] > arr[i+1])
            e_ok = 0;
    }
    cout<<"E sortat: ";
    return e_ok;
}


int main()
{

ifstream myfile("FIN.txt");
myfile>>T;

for(int test = 1; test<=T; test++)
{
    myfile>>N>>MAX;
    cout<<"_________________________________________________________________"<<endl<<endl;
    cout<<"Testul "<<test<<": "<<N<<" numere cu valoarea maxima "<<MAX<<endl<<endl;
    generare_vector(N, MAX, vec);
    Bubblevec.assign(vec.begin(), vec.end());
    Countvec.assign(vec.begin(), vec.end());
    Radixvec.assign(vec.begin(), vec.end());
    Radixvec16.assign(vec.begin(), vec.end());
    Radixvec256.assign(vec.begin(), vec.end());
    Mergevec.assign(vec.begin(), vec.end());
    Quickvec.assign(vec.begin(), vec.end());
    Insertvec.assign(vec.begin(), vec.end());
    Timvec.assign(vec.begin(), vec.end());

    auto start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

}

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();

    for(unsigned long int i=10; i>0; i--)
    {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
    }
cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 10 ELEMENTS___________________________"<<endl<<endl;

    auto start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();
        for(unsigned long int i=100; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }
        cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 100 ELEMENTS___________________________"<<endl<<endl;

    start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();
        for(unsigned long int i=1000; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }
           cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 1000 ELEMENTS___________________________"<<endl<<endl;

    start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;


    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();


        for(unsigned long int i=10000; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }

        cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 10000 ELEMENTS___________________________"<<endl<<endl;

        start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();
        for(unsigned long int i=100000; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }

        cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 100000 ELEMENTS___________________________"<<endl<<endl;

        start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();
        for(unsigned long int i=1000000; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }

        cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 1000000 ELEMENTS___________________________"<<endl<<endl;

        start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();
        for(unsigned long int i=10000000; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }

        cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 10000000 ELEMENTS___________________________"<<endl<<endl;

        start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();
        for(unsigned long int i=100000000; i>0; i--)
        {
        vecAUX.push_back(i);
        Bubblevec.push_back(i);
        Countvec.push_back(i);
        Radixvec.push_back(i);
        Radixvec16.push_back(i);
        Radixvec256.push_back(i);
        Mergevec.push_back(i);
        Quickvec.push_back(i);
        Insertvec.push_back(i);
        Timvec.push_back(i);
        }

        cout<<"___________________________DESCENDING ORDER VECTORS: INCREASING IN SIZE. NOW: 100000000 ELEMENTS___________________________"<<endl<<endl;

        start = high_resolution_clock::now();
    sort(vecAUX.begin(), vecAUX.end());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by the sort() function TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds" << endl<<endl;

    start = high_resolution_clock::now();
    BubbleSort(Bubblevec, Bubblevec.size());
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by Bubble TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Bubblevec)<<" pentru BUBBLE"<<endl<<endl;

    start = high_resolution_clock::now();
    CountSort(Countvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by COUNT SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Countvec)<<" pentru COUNT"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort(Radixvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT CLASSIC TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec)<<" pentru RADIX CLASIC"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort16(Radixvec16);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 16 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec16)<<" pentru RADIX BASE 16"<<endl<<endl;

    start = high_resolution_clock::now();
    RadixSort256(Radixvec256);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by RADIX SORT BASE 256 TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Radixvec256)<<" pentru RADIX BASE 256"<<endl<<endl;

    start = high_resolution_clock::now();
    MergeSort(Mergevec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by MERGE SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Mergevec)<<" pentru MERGE"<<endl<<endl;

    start = high_resolution_clock::now();
    QuickSort(Quickvec, 0, Quickvec.size() - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by QUICK SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Quickvec)<<" pentru QUICK"<<endl<<endl;

    start = high_resolution_clock::now();
    InsertionSort(Insertvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by INSERTION SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Insertvec)<<" pentru INSERTION"<<endl<<endl;

    start = high_resolution_clock::now();
    TimSort(Timvec);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    cout<<"Time taken by TIM SORT TO SORT DESCENDIND ORDER VECTOR: "<<duration.count()<<" microseconds"<<endl;
    cout<<test_sort(Timvec)<<" pentru TIM"<<endl<<endl;

    vecAUX.clear();
    Bubblevec.clear();
    Countvec.clear();
    Radixvec.clear();
    Radixvec16.clear();
    Radixvec256.clear();
    Mergevec.clear();
    Quickvec.clear();
    Insertvec.clear();
    Timvec.clear();



return 0;
}
