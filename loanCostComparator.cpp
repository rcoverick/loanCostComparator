#include<iostream>
#include<string>
#include<iostream>
#include<vector>
#include<cmath> 

using namespace std; 


class AmortizationEntry {
    
    public:
        double totalPayment; 
        double principalPayment; 
        double interestPayment; 
        double newLoanAmount; 
        AmortizationEntry(double,double,double,double);

};


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

class Loan {
    int amount;
    double interest;
    int duration;
    int extraPrincipalPayment;
    
    public:
        Loan(int,double,int,int);
        vector<AmortizationEntry> getAmortiztionSchedule();
        double getMonthlyPayment();
        int getAmount();
        double getInterestRate();
    private:
};

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

/**
 * @brief Get the Breakeven point during the loan payment schedules. 
 * 
 * The breakeven point is defined as the point where the larger of the two loans 
 * (based on first entry principal , using interest payment as a tiebreaker)
 * has an equal or lesser amount of interest paid on the amortization schedule. 
 * 
 * returns an int representing the nth payment which is the payment that is the breakeven point.
 * @param loan1 
 * @param loan2 
 * @return int 
 */
int getBreakevenPayment(Loan *loan1, Loan *loan2){
    bool isLoan1Bigger = loan1->getAmount() > loan2->getAmount() ||
                        (loan1->getAmount() == loan2->getAmount()) && loan1->getInterestRate() > loan2->getInterestRate();
    Loan *largerLoan = loan1;
    Loan *smallerLoan = loan2;
    if(isLoan1Bigger){
        largerLoan = loan1;
        smallerLoan = loan2;
    } else {
        largerLoan = loan2;
        smallerLoan = loan1;
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

int main(){
    printWelcomeMessage();
    Loan l1 = getLoanInfoFromCli();
    cout<<"---"<<endl<<"Second Loan"<<endl;
    Loan l2 = getLoanInfoFromCli();
    int interestBreakevenPoint = getBreakevenPayment(&l1,&l2);
    cout<<"The larger loan hits breakeven at payment "<<interestBreakevenPoint<<endl;
    return 0;  
}