#include<iostream>
#include<string>
#include<iostream>
#include<cmath> 
#include "Loan.h"

using namespace std; 


void printWelcomeMessage(){ 
    cout<<"Loan Amortization Comparator"
    <<endl 
    <<"Compare the interest rate payments and breakeven points between multiple loans and payment schemes"
    <<endl 
    <<"---"<<endl;
    return;
}

int readIntFromUser(string prompt){
    string i;
    cout<<prompt;
    getline(cin, i);
    return stoi(i);
}

int readDoubleFromUser(string prompt){
    string i;
    cout<<prompt;
    getline(cin, i);
    return stod(i);   
}

Loan getLoanInfoFromCli(){
    int loanAmount = readIntFromUser("Enter total loan amount($): ");
    double loanInterest = readDoubleFromUser("Enter interest rate (%): ");
    int loanTimeMonths = readIntFromUser("Enter number of months of loan: ");
    int loanAddlPayment = readIntFromUser("Enter extra principal payment monthly ($): ");
    return Loan(loanAmount,loanInterest,loanTimeMonths,loanAddlPayment);
}

int main(){
    printWelcomeMessage();
    Loan l1 = getLoanInfoFromCli();
    cout<<"---"<<endl<<"Second Loan"<<endl;
    Loan l2 = getLoanInfoFromCli();
    int interestBreakevenPoint = l1.getBreakevenPayment(&l2);
    cout<<"The larger loan hits breakeven at payment "<<interestBreakevenPoint<<endl;
    return 0;  
}