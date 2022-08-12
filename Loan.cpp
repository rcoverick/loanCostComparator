#include "Loan.h"
#include<cmath>
#include<iostream>
#include<string>

using namespace std;

std::ostream& operator<<(std::ostream &s, const AmortizationEntry &a){
    return s<<"AmortizationEntry["
    <<"totalPayment: "<<to_string(a.totalPayment)<<", "
    <<"principalPayment: "<<to_string(a.principalPayment)
    <<", interestPayment: "<<to_string(a.interestPayment)<<", newLoanAmount: "<<to_string(a.newLoanAmount)<<"]";
}

AmortizationEntry::AmortizationEntry(double t, double p, double i, double n){
    totalPayment = t;
    principalPayment = p;
    interestPayment = i;
    newLoanAmount = n;
}


Loan::Loan(int a, double i, int d, int e){
    amount = a;
    interest = i;
    duration = d;
    extraPrincipalPayment = e;
}

double Loan::getMonthlyPayment(){
    double i = interest / 100 / 12;
    double numerator = i * pow(1+i, duration); 
    double denominator  = pow(1+i, duration) -1; 
    return amount * (numerator / denominator);
}

int Loan::getAmount(){
    return amount;
}

double Loan::getInterestRate(){ 
    return interest;
}

vector<AmortizationEntry> Loan::getAmortiztionSchedule(){
    vector<AmortizationEntry> schedule;
    double remainingAmount = amount; 
    double monthlyInterest;
    double totalMonthlyPayment = getMonthlyPayment();
    double monthlyPrinicpal;
    while(remainingAmount > 0){
        monthlyInterest = remainingAmount * (interest / 100 / 12); 
        monthlyPrinicpal = totalMonthlyPayment - monthlyInterest;
        schedule.push_back(AmortizationEntry(totalMonthlyPayment + extraPrincipalPayment,
                                              monthlyPrinicpal,
                                              monthlyInterest, 
                                              remainingAmount - monthlyPrinicpal - extraPrincipalPayment));
        remainingAmount -= (monthlyPrinicpal + extraPrincipalPayment);
    }
    return schedule;
}


/**
 * @brief Get the Breakeven point during the loan payment schedules. 
 * 
 * The breakeven point is defined as the point where the larger of the two loans 
 * (based on first entry principal , using interest payment as a tiebreaker)
 * has an equal or lesser amount of interest paid on the amortization schedule. 
 * 
 * returns an int representing the nth payment which is the payment that is the breakeven point.
 * @param other - the loan being compared to this loan  
 * @return int 
 */

int Loan::getBreakevenPayment(Loan *other){
    bool isLoan1Bigger = this->getAmount() > other->getAmount() ||
                    (this->getAmount() == other->getAmount()) && this->getInterestRate() > other->getInterestRate();
    Loan *largerLoan = this;
    Loan *smallerLoan = other;
    if(isLoan1Bigger){
        largerLoan = this;
        smallerLoan = other;
    } else {
        largerLoan = other;
        smallerLoan = this;
    }
    vector<AmortizationEntry> largerLoanAmortization = largerLoan->getAmortiztionSchedule();
    vector<AmortizationEntry> smallerLoanAmortization = smallerLoan->getAmortiztionSchedule();

    for(
        int i = 0;
        i<smallerLoanAmortization.size();
        i++
    ){
        bool isBreakeven = largerLoanAmortization[i].interestPayment < smallerLoanAmortization[i].interestPayment;
         
        if(isBreakeven){
            cout<<"---"<<"\n - "<<largerLoanAmortization[i]<<endl<<smallerLoanAmortization[i]<<endl;
            return i;
        }
    }
    return -1;
}

