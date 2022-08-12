#ifndef LOAN_H
#define LOAN_H
#include<vector>
#include<iostream>


class AmortizationEntry {
    
    public:
        double totalPayment; 
        double principalPayment; 
        double interestPayment; 
        double newLoanAmount; 
        AmortizationEntry(double,double,double,double);

};


class Loan {
    int amount;
    double interest;
    int duration;
    int extraPrincipalPayment;
    
    public:
        Loan(int,double,int,int);
        std::vector<AmortizationEntry> getAmortiztionSchedule();
        double getMonthlyPayment();
        int getAmount();
        double getInterestRate();
        int getBreakevenPayment(Loan *other);

};

std::ostream& operator<<(std::ostream &s, const AmortizationEntry &a);
#endif
