#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include<limits.h>

#ifdef _WIN32                                       //Checking OS
    #define OS 0
    #include<windows.h>
#endif

#ifdef APPLE
    #define OS 1
    #include<unistd.h>
#endif

#ifdef unix
    #define OS 1
    #include<unistd.h>
#endif

const int vmachine = 3;
const int INF = 1e9;
int distance_each[5][5]={0,200,250,90,80,
                     200,0,80,110,78,
                     250,80,0,120,76,
                     90,-1,120,0,-1,
                     86,54,-1,65,0};

int nofEvent[5]={0};

#define ffr(i,n) for(int i=0;i<n;i++)
#define fl(n) for(int i=0;i<n;i++)

using namespace std;

vector<vector<int>> graph(5, vector<int>(5));

int days[30]={0}; 
int netTotalCost = 0;
int coins[] = {1,2,5,10,20,50,100};
vector<int>coin_returned;
int minCoins(int V, vector<int>& coins_returned)
{

    // table[i] will be storing the minimum number of coins
    // required for i value. So table[V] will have result
    int table[V + 1];
    int m=7;
    // Base case (If given value V is 0)
    table[0] = 0;

    // Initialize all table values as Infinite
    for (int i = 1; i <= V; i++)
        table[i] = INT_MAX;

    // Compute minimum coins required for all
    // values from 1 to V
    for (int i = 1; i <= V; i++)
    {
        // Go through all coins smaller than i
        for (int j = 0; j < m; j++)
            if (coins[j] <= i)
            {
                int sub_res = table[i - coins[j]];
                if (sub_res != INT_MAX
                    && sub_res + 1 < table[i])
                    table[i] = sub_res + 1;
            }
    }

    if (table[V] == INT_MAX)
        return -1;

    // Compute coins to be returned
    int remaining_value = V;
    while (remaining_value > 0)
    {
        for (int j = 0; j < m; j++)
        {
            if (coins[j] <= remaining_value && table[remaining_value - coins[j]] == table[remaining_value] - 1)
            {
                coins_returned.push_back(coins[j]);
                remaining_value -= coins[j];
                break;
            }
        }
    }

    return table[V];
}

void vending()
{
    drink:
    // details of drinks available in vending machine........
    cout<<"Drinks available in vending machines are :- "<<"       Name         " <<" Price(in rupees)"<<endl<<endl;
    cout<<setw(50)<<" "<<" 1.COCA COLA    "<<"  57   "<<endl<<endl;
    cout<<setw(50)<<" "<<" 2.PEPSI         "<<"  48   "<<endl<<endl;
    cout<<setw(50)<<" "<<" 3.STING         "<<"  35   "<<endl<<endl;
    cout<<setw(50)<<" "<<" 4.MINERAL WATER "<<"  25   "<<endl<<endl;
    cout<<setw(50)<<" "<<" 5.THANDAI       "<<"  89   "<<endl<<endl;
    // choice to enter in the machine............
    int choice;
    cout<<"Enter your choice :";
    cin>>choice;
    cout<<endl;
    if(choice<1 || choice>5)
    {
        cout<<"Wrong choice !!!......."<<endl;
        cout<<"Press 1 to renter the choice Or any other Number to quit"<<endl;
        int re;
        cin>>re;
        if(re==1)
        {
            system("cls");
            goto drink;
        }

        else 
            return ;
    }
    am:
    int amount;
    cout<<"Enter the amount(more than 100)"<<endl;
    cin>>amount;
    if(amount>=100)
    {
        cout<<"Amount accepted :)"<<endl;
        goto pm;
    }
    else {
        cout<<"Rejected ........!"<<endl;
        goto am;
    }

    pm:
    // to get the minimum no of coins used and which coin
    // using changed minimum coin exchange problem
    int mincoin;
    if(choice==1)
    {
       mincoin= minCoins(amount-57,coin_returned);
    }
    else
    if(choice==2)
    {
        mincoin=minCoins(amount-48,coin_returned);
    }
    else
    if(choice==3)
    {
        mincoin=minCoins(amount-35,coin_returned);
    }
    else
    if(choice==4)
    {
        mincoin=minCoins(amount-25,coin_returned);
    }
    else
    if(choice==5)
    {
        mincoin=minCoins(amount-89,coin_returned);
    }
    if (mincoin == -1)
        cout << "It is not possible to get the exact change  ";
    else
    {
        cout << "Coins to be returned: ";
        for (int i = 0; i < coin_returned.size(); i++)
            cout << coin_returned[i] << " ";
        cout << "\n";
    }
}

void vendingMain(){
    cout<<"Want something from the Vending Machine so what are you waiting from "<<endl;
    vend:
    vending();
    cout<<"Wish to buy Another Drink ? (press a to continue...) "<<endl;
    char abc;
    cin>>abc;
    if(abc=='a'){
        system("cls");
        goto vend;
    }
    else
        cout<<"Thank You for visiting :)(:"<<endl;
    return;
}


void parking()
{
   string lane[3],lane1,lane2,lane3;
    int m=0;
    ifstream fReader("parking.txt",ios::in);
    if(!fReader){ cout<<"Error in Opening file"; return;}
    while (getline(fReader,lane2)){
        lane[m]=lane2;
        m++;
    }
    fReader.close();
    ofstream fWriter("parking.txt",ios::out);
    if(!fWriter){ cout<<"Error in Opening file"; return;}
    for(int i=0;i<25;i++){
        if(lane[0][i]=='0'){
            cout<<"YOUR TOKEN NO FOR PARKING IS "<<i+1;
            lane[0][i]='1';
            cout << endl;
            // for (auto i:lane[0]){cout << i <<'\t';}cout << endl;
            // for (auto i:lane[1]){cout << i <<'\t';}cout << endl;
            // for (auto i:lane[2]){cout << i <<'\t';}cout << endl;
            fWriter << lane[0] << endl;
            fWriter << lane[1] << endl;
            fWriter << lane[2] << endl;
            fWriter.close();
            return;
        }
    }
    for(int i=0;i<25;i++){
        if(lane[1][i]=='0'){
            cout<<"YOUR TOKEN NO FOR PARKING IS"<<26+i;
            lane[1][i]='1';
            fWriter << lane[0] << endl;
            fWriter << lane[1] << endl;
            fWriter << lane[2] << endl;
            fWriter.close();
            return;
        }
    }
    for(int i=0;i<25;i++){
        if(lane[2][i]=='0'){
            cout<<"YOUR TOKEN NO FOR PARKING IS"<<51+i;
            lane[2][i]='1';
            fWriter << lane[0] << endl;
            fWriter << lane[1] << endl;
            fWriter << lane[2] << endl;
            fWriter.close();
            return;
        }
    }
    cout<<"PARKING IS FULL";
}

void begin()
{
    fl(4)
    {
    fl(6)
    cout<<endl;
    cout <<setw(30)<<" "<< "      o      "<<"      o      "<<"      o      "<<"      o      "<<endl;
    cout <<setw(30)<<" "<< "     <|>     "<<"     <|>     "<<"     <|>     "<<"     <|>     "<<endl;
    cout <<setw(30)<<" "<< "     / \\     "<<"     / \\     "<<"     / \\     "<<"     / \\     "<<endl;
    cout <<setw(30)<<" "<< "    /   \\    "<<"    /   \\    "<<"    /   \\    "<<"    /   \\    "<<endl;
      Sleep(120);
    system("cls");
    fl(6)
    cout<<endl;
    cout <<setw(30)<<" "<< "   <o> <o>   "<<"   <o> <o>   "<<"   <o> <o>   "<<"   <o> <o>    "<<endl;
    cout <<setw(30)<<" "<< "    |   |    "<<"    |   |    "<<"    |   |    "<<"    |   |     "<<endl;
    cout <<setw(30)<<" "<< "   / \\ / \\   "<<"   / \\ / \\   "<<"   / \\ / \\   "<<"   / \\ / \\   "<<endl;
    cout <<setw(30)<<" "<< "  /   \\   \\  "<<"  /   \\   \\  "<<"  /   \\   \\  "<<"  /   \\   \\  "<<endl;
      Sleep(120);
      system("cls");
      fl(6)
    cout<<endl;
    cout <<setw(30)<<" "<< "    \\ o /    "<<"    \\ o /    "<<"    \\ o /   "<<"    \\ o /    "<<endl;
    cout <<setw(30)<<" "<< "      |      "<<"      |      "<<"      |     "<<"      |      "<<endl;
    cout <<setw(30)<<" "<< "     / \\     "<<"     / \\     "<<"     / \\     "<<"     / \\     "<<endl;
    cout <<setw(30)<<" "<< "    /   \\    "<<"    /   \\    "<<"    /   \\    "<<"    /   \\    "<<endl;

Sleep(120);
system("cls");
fl(6)
    cout<<endl;
    cout <<setw(30)<<" "<< "   __ o __   "<<"   __ o __   "<<"   __ o __  "<<"   __ o __   "<<endl;
    cout <<setw(30)<<" "<< "      |      "<<"      |      "<<"      |     "<<"      |      "<<endl;
    cout <<setw(30)<<" "<< "     / \\     "<<"     / \\     "<<"     / \\     "<<"     / \\     "<<endl;
    cout <<setw(30)<<" "<< "    /   \\    "<<"    /   \\    "<<"    /   \\    "<<"    /   \\    "<<endl;

Sleep(120);
system("cls");
    }
}

void welcome()
{
    time_t s, val = 1;
    struct tm* current_time;
    // time in seconds
    s = time(NULL);
    // to get current time
    current_time = localtime(&s);
    // print time in minutes,
    // hours and seconds
    cout<<endl;
    cout<<setw(105);
    cout<<current_time->tm_hour<<" : "<<current_time->tm_min<<" : "<<current_time->tm_sec;



    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<setw(25)<<" "<<" _____                                  _____                                   "<<endl;
    cout<<setw(25)<<" "<<"|        ___                           |                                        "<<endl;
    cout<<setw(25)<<" "<<"|       |   |  _____       _____       |      \\        /  ____  |\\    | ______"<<endl;
    cout<<setw(25)<<" "<<"|_____  |___|    |        |            |_____  \\      /  |      | \\   |    |  "<<endl;
    cout<<setw(25)<<" "<<"|       |        |        |            |        \\    /   |____  |  \\  |    |  "<<endl;
    cout<<setw(25)<<" "<<"|       |        |        |            |         \\  /    |      |   \\ |    |  "<<endl;
    cout<<setw(25)<<" "<<"|_____  |      __|__      |_____       |_____     \\/     |____  |    \\|    |  "<<endl;
    cout<<endl<<endl<<endl;
    cout <<setw(45)<<" "<< "WELCOME TO THE EPIC EVENT...organized by\n\n";
    cout<<setw(50)<<" " << "ANMOL VERMA - 21803014 - B12\n";
    cout<<setw(50)<<" " << "HARSHIT VIJAY - 21803015 - B12\n";
    cout<<setw(50)<<" " << "ROHIT GUPTA - 21803018 - B12\n";
    getchar();
    system("cls");
}

void place()
{
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<setw(25)<<"  "<<" ______________________________________________________________________________________________________ "<<endl;
    cout<<setw(25)<<"  "<<"|  Laboratory   |               AUDITORIUM               |                        |                    |"<<endl;
    cout<<setw(25)<<"  "<<"|  cost:1000    |               cost:25000               |                        |                    |"<<endl;
    cout<<setw(25)<<"  "<<"| capacity:250  |               capacity:10000           |                        |                    |"<<endl;
    cout<<setw(25)<<"  "<<"| |___________| |____________              ____________| |                        |                    |"<<endl;
    cout<<setw(25)<<"  "<<"|                            |            |                                       |                    |"<<endl;
    cout<<setw(25)<<"  "<<"|                            |            |                                       |                    |"<<endl;
    cout<<setw(25)<<"  "<<"|_____| |_______|_____       |    ____    |              _______|  |_______       |____________________|"<<endl;
    cout<<setw(25)<<"  "<<"|   PORTICO     |     |      |____|  |____|             | Lecture Threater |      |       OAT          |"<<endl;
    cout<<setw(25)<<"  "<<"|  cost:3000    |_____|_                                |    cost:5000     |      |    cost:10000      |"<<endl;
    cout<<setw(25)<<"  "<<"| capacity:1000 |       |                               |  capacity:2000   |      |   capacity:8000    |"<<endl;
    cout<<setw(25)<<"  "<<"|_______________|_______|_______________________________|__________________|______|____________________|"<<endl;
    getchar();
    system("cls");
}


class subeventDetails{
public:
    string eventName;
    int estimatedFootfall;
    int startTime;
    int endTime;
    int assigned_place = -1; // initialize to -1 to indicate unassigned
    void getDetails(){
        cout << "Name of SubEvent: ";
        cin >> eventName;
        cout << "Estimated Footfall of the Subevent = ";
        cin >> estimatedFootfall;
        cout << "Starting Time of the SubEvent (acc. to 24Hr. Time Schedule) - " << eventName << " : ";
        cin >> startTime;
        cout << "Ending Time of the SubEvent (acc. to 24Hr. Time Schedule) - " << eventName << " : ";
        cin >> endTime;
    }
};

bool value(subeventDetails const & a,subeventDetails const & b)
{
    return a.estimatedFootfall>b.estimatedFootfall;
}

class placeDetails{
public:
    string placeName;
    int capacity;
    int cost;
    vector<int> assigned_events;
    placeDetails(){placeName="";capacity=0,cost=0;}
    placeDetails(string a,int b,int c){placeName=a;capacity=b,cost=c;}
    void showDetails(){
        cout <<endl<<endl<<endl;
        cout << setw(50) << " " << "Place Name: " << placeName << endl; 
        cout << setw(50) << " " << "Capacity: " << capacity << endl; 
        cout << setw(50) << " " << "Cost: " << cost << endl; 
    }
    friend std::ostream& operator<<(std::ofstream& out,placeDetails& obj){
        out << obj.placeName << ';' << obj.capacity << ';' << obj.cost;
        return out;
    }
    friend std::ifstream& operator>>(std::ifstream& in,placeDetails& obj){
        in >> obj.placeName >> obj.capacity >> obj.cost;
        return in;
    }

    void attributeExtractor(string input){
        vector<string> attributes;
        int startIndex = 0, endIndex = 0;
        for (int i=0; i<=input.size(); i++) {
            if (input[i] == ';' || i == input.size()) {
                endIndex = i;
                string temp;
                temp.append(input, startIndex, endIndex - startIndex);
                attributes.push_back(temp);
                startIndex = endIndex + 1;
            }
        }
        int ct=0;
        while (ct<3){
            // this has to be changed depending on the number of attributes of an object
            switch (ct){
            case 0:
                this->placeName=attributes[ct];
                ct++;
                break;
            case 1:
                this->capacity=stoi(attributes[ct]);
                ct++;
                break;
            case 2:
                this->cost=stoi(attributes[ct]);
                ct++;
                break;
            }
        }
    }
};


vector<placeDetails> placefileReader(){
    vector<placeDetails> pdetailsVec; 
    ifstream placeReader("places.txt",ios::in);
    if(!placeReader){ cout<<"Error in Opening file"; return pdetailsVec;}
    string line;
    while (getline(placeReader,line)){
        placeDetails temp;
        temp.attributeExtractor(line);
        pdetailsVec.push_back(temp);
    }
    placeReader.close();
    return pdetailsVec;
}
void pdtoFile(){
    ofstream placeWriter("places.txt",ios::out);
    if(!placeWriter){ cout<<"Error in Opening file"; return;}
    placeDetails audi("Auditorium",10000,25000);
    placeWriter << audi << endl;
    placeDetails oat("OAT",8000,10000);
    placeWriter << oat << endl;
    placeDetails lt("LectureThereater",2000,5000);
    placeWriter << lt << endl;
    placeDetails port("Portico",1000,3000);
    placeWriter << port << endl;
    placeDetails cslab("Laboratory",250,1000);
    placeWriter << cslab << endl;
    placeWriter.close();
}


class programDetails{
public:
    string name;
    double phoneNo;
    int fday; // First date of event
    int eventDuration;
    vector<int> numOfEventEachDay;
    vector<vector<subeventDetails>> subevent;

    friend std::ostream& operator<<(std::ofstream& out,programDetails& obj){
        out << obj.name << ';' << obj.phoneNo << ';' << obj.fday << ';' << obj.eventDuration << ';'; 

        for (int i=0;i<obj.eventDuration;i++){
            out << obj.numOfEventEachDay[i];
            for (int j=0;j<obj.numOfEventEachDay[i];j++){
                out << ",";
                out << obj.subevent[i][j].eventName << "!" << obj.subevent[i][j].estimatedFootfall << "!"<< obj.subevent[i][j].startTime << "!" << obj.subevent[i][j].endTime << "!" << obj.subevent[i][j].assigned_place;
            }
            out << ";";
        }
        return out;
    }

    friend std::istream& operator>>(std::ifstream& in,programDetails& obj){
        in>>obj.name>>obj.phoneNo>>obj.fday>>obj.eventDuration; 

        for (int i=0;i<obj.eventDuration;i++){
            in>>obj.numOfEventEachDay[i];
            for (int j=0;j<obj.numOfEventEachDay[i];j++){
                in>>obj.subevent[i][j].eventName>>obj.subevent[i][j].estimatedFootfall>>obj.subevent[i][j].startTime>>obj.subevent[i][j].endTime>>obj.subevent[i][j].assigned_place;
            }
        }
        return in;
    }

    void getDetails(){
        cout<<"Enter Your Name: ";
        cin>>name;
        cout << "Contact Number of the Organizer: ";
        cin >> phoneNo;
        date:
        cout<<endl<<"The Program Should Start on (Day of Month): ";
        cin>>fday;
        if(fday>30){
            cout<<"This Date doesn't exist \nReEnter the Date"<<endl;
            goto date;
        }
        days:
        cout<<endl<<"Duration Of Event (Number of Days) :";
        cin>>eventDuration;
        if(eventDuration>10){
            cout<<"Sorry we don't plan for this much long...\n";
            cout<<"Do you want to re-enter duration ? (press 1 to continue) ... ";
            int m;
            cin>>m;
            if(m==1) goto days;
            else return;
        }
        bool flag=false;
        ffr(i,eventDuration){
            if(days[fday+i]!=0){
                cout<<endl<<"This Day has already have been booked"<<endl;
                flag=true;
                break;
            }
        }
        if(flag==true){
            cout<<"Want to Re-enter the day? (press 1 to continue) ... "<<endl;
            cout<<"Want to see available dates? (press 2 to continue) ... "<<endl;
            cout<<"To Quit (press any other number) ... "<<endl;
            int l;
            cin>>l;
            if(l==1) goto date;
            else {
                if(l==2) goto c;
                else return;
            }
        }
        else{
            cout<<endl<<"Your Event has been booked!! :)\n";
            for (int i=0;i<eventDuration;i++){
                days[fday+i-1]=1;            
            }
            for (int i=0;i<eventDuration;i++){
                int temp;
                cout << "Enter the Number of events on Day-"<<i+1<<": ";
                cin >> temp;
                numOfEventEachDay.push_back(temp);
                vector<subeventDetails> tempvec;
                for (int i=0;i<temp;i++){
                    subeventDetails tempobj;
                    tempobj.getDetails();
                    tempvec.push_back(tempobj);
                }
                sort(tempvec.begin(),tempvec.end(),value);
                vector<placeDetails> places = placefileReader();
                int totalDayCost = 0;
                // assign events to places
                for (int i = 0; i < temp; i++) {
                    int best_place = -1;
                    int best_cost = INT_MAX;
                    int best_distance = INT_MAX;
                // find the best place to assign the event
                    for (int j = 0; j < 5; j++) {
                        if (places[j].capacity*1.1 >= tempvec[i].estimatedFootfall) {
                            int cost = places[j].cost;
                            int distance = abs(tempvec[i].startTime- tempvec[i].endTime) + abs(tempvec[i].endTime - tempvec[i].startTime);
                            if (cost < best_cost || (cost == best_cost && distance < best_distance)) {
                                // CONFLICT MANAGMENT
                                bool is_conflict = false;
                                for (int k = 0; k < places[j].assigned_events.size(); k++) {
                                    int assigned_event = places[j].assigned_events[k];
                                    if (tempvec[assigned_event].startTime< tempvec[i].endTime && tempvec[assigned_event].endTime > tempvec[i].startTime) {
                                        is_conflict = true;
                                        break;
                                    }
                                }
                                if (!is_conflict) {
                                    best_place = j;
                                    best_cost = cost;
                                    best_distance = distance;
                                }
                            }
                        }
                    }
                    nofEvent[best_place]++;
                    totalDayCost+=best_cost;
                    // assign event to best place
                    if (best_place != -1) {
                        tempvec[i].assigned_place = best_place;
                        places[best_place].assigned_events.push_back(i);
                    }
                }
                // print assigned events for each place
                for (int i = 0; i < 5; i++) {
                    cout << places[i].placeName << " : ";
                    for (int j = 0; j < places[i].assigned_events.size(); j++) {
                        int assigned_event = places[i].assigned_events[j];
                        cout << tempvec[assigned_event].eventName << " ";
                    }
                    cout << endl;
                }
                cout << "Total Day cost = " << totalDayCost << endl;
                subevent.push_back(tempvec);
            }
            return;
        }
        c:
        cout<<endl<<"The days where you can plan your event are: \n";
        int l=0;
        ffr(i,30){
            if(days[i]==0) {l++;}
            else {l=0;}
            if(l==eventDuration){
                cout<< i-eventDuration+1 <<'\t';
                l=l-1;
            }
            cout << endl;
        }
    }
};



void programDetailToFile(programDetails &obj){
    ofstream progWriter("programsDesc.txt",ios::out);
    if (!progWriter){
        cout << "Error in Opening File";
        return;
    }
    progWriter << obj << endl;
}


void closeDist() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
        graph[i][j]=distance_each[i][j];
            if (graph[i][j] == -1) {
                graph[i][j] = INF;
            }
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }   
}

void printShortDist(){
    closeDist();
    vector<placeDetails> temp = placefileReader();
    // Print shortest distances
    cout << setw(20) << " ";
    for (int i=0;i<5;i++){
        cout << setw(30) << temp[i].placeName;   
    }
    cout << endl;
    for (int i = 0; i < 5; i++) {
        cout << setw(20) << " " << temp[i].placeName ;
        for (int j = 0; j < 5; j++) {
            if (graph[i][j] == INF) cout << "INF ";
            else cout << setw(15) << graph[i][j] << "           ";
        }
        cout << endl;
    }
}


// Function to find the optimal locations for placing 3 vending machines
vector<int> findVendingMachineLocations(vector<vector<int>>& dist) {
    closeDist();
    int n = dist.size();
    vector<int> C; // Initialize an empty set C for vending machine locations
    int firstMachine = rand() % n; // Choose an arbitrary node as the first vending machine
    C.push_back(firstMachine);
    while(C.size() < 3) {
        int maxDist = -1, nextMachine = -1;
        for(int u=0; u<n; u++) {
            if(find(C.begin(), C.end(), u) != C.end()) {
                continue; // Skip nodes already in C
            }
            int minDist = INT_MAX;
            for(int v : C) {
                minDist = min(minDist, dist[u][v]); // Compute the minimum distance between u and any node in C
            }
            if(minDist > maxDist) {
                maxDist = minDist;
                nextMachine = u;
            }
        }
        C.push_back(nextMachine); // Add the node with the maximum minimum distance to C
    }
    return C;
}

void searchName(string nametoBeSearched){
    ifstream allDReader("allDetails.txt",ios::in);
    if (!allDReader){
        cout << "Error in Opening File";
        return;
    }
    string line;
    while (getline(allDReader,line)){
        char delimiter = ';';
        size_t pos = line.find(delimiter);
        if (pos != string::npos) {
        // The delimiter exists in the string
            string first_part = line.substr(0, pos); // Get the first part
            if (first_part == nametoBeSearched){
                cout << "Your Event Has been Booked!! ... Thank You for Booking with us :)\n";
                allDReader.close();
                return;
            }
        }
    }
    cout << "No Booking Found for this Name!! ... :(\n";
    allDReader.close();
    return ;
}

int main(){
    begin();
    welcome();
    place();
    closeDist();
    pdtoFile(); 
    vector<placeDetails> pDetails = placefileReader();
    ifstream schReader("schedule.txt",ios::in);
    if (!schReader){
        cout << "ERROR OCCURED!!...";
        cout << "\nError Code: FH-R\n"; //File Handling Reading
        return -1;
    }
    string line;
    getline(schReader,line);
    for (int i=0;i<30;i++){
        days[i] = int(line[i])-48; // 48 is the ASCII value of '0'
    }
    schReader.close();

    int ch;
    chocie:
    cout << "\n\n\nPress 1 to Book an Event! ... \n";
    cout << "Press 2 to Search if You have booked an Event! ... \n";
    cout << "Press 3 to Use Vending Machine! ... \n";
    cout << "Press 4 to Use Parking Automation! ... \n";
    cout << "Press 5 to Display the location of Vending Machines! ... \n";
    cout << "Press 6 to Exit! ... \n\n\n\n";
    cin >> ch;
    if (ch==1){
        system("cls");
        programDetails p1;
        p1.getDetails();
        ofstream allDWriter("allDetails.txt",ios::out);
        if (!allDWriter){
            cout << "Error in Opening File";
            return -1;
        }
        allDWriter << p1 << endl;
        allDWriter.close();
        ofstream schWriter("schedule.txt",ios::out);
        if (!schWriter){
            cout << "ERROR OCCURED!!...";
            cout << "\nError Code: FH-W\n"; //File Handling Writing
            return -1;
        }
        ffr(i,30){schWriter << days[i];}
        schWriter.close();
        goto chocie;
    }
    else if (ch==2){
        system("cls");
        string sName;
        cout << "Enter The name in whose Event has Booked ... ";
        cin >> sName; 
        searchName(sName);
        goto chocie;
    }
    else if (ch==3){
        system("cls");
        vendingMain();
        goto chocie;
    }
    else if (ch==4){
        system("cls");
        parking();
        goto chocie;
    }
    else if(ch==5){
        system("cls");
        cout << "The optimal locations for placing the vending machines are: ";
        vector<int>C = findVendingMachineLocations(graph);
        for(int i=0; i<C.size(); i++) {
            cout << pDetails[C[i]].placeName << " ";
        }
        cout << endl;
        getchar();
        getchar();
        goto chocie;
        return 0;
    }

    else if(ch==6){
        system("cls");
        cout << "Thanking You for Using...\n\n";
        // goto chocie;
        return 0;
    }
    else{
        cout << "INVALID CHOICE!!...\n";
        goto chocie;
        return 0;
    }
    return 0;
}   