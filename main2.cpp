#include <iostream>

using namespace std;

class term {
	friend class polynomial;
    int Coefficent;  
    int Exponent;
    term* next;
    term(int C,int E){
    	Coefficent = C;
    	Exponent = E;
	}
};

class polynomial {
private:
    term* head;

public:
    polynomial(){
    	head = nullptr;
	}
    void addTerm(int Coeff, int Exp) {
        if (Coeff == 0) {
        	return;
		}
        term* newTerm = new term(Coeff,Exp);
        
        if (!head || Exp > head->Exponent) {
            newTerm->next = head;
            head = newTerm;
        } else {
            term* courser = head;
            term* previous = nullptr;

            while (courser != nullptr && courser->Exponent >= Exp) {
                if (courser->Exponent == Exp) {
                    courser->Coefficent += Coeff;
                    delete newTerm;
                    return;
                }
                previous = courser;
                courser = courser->next;
            }
            newTerm->next = courser;
            previous->next = newTerm;
        }
    }


    void print(){
        term* courser = head;
        while (courser != nullptr) {
            cout <<'('<< courser->Coefficent << "x**" << courser->Exponent<<')';
            if (courser->next != nullptr) {
            	cout << " + ";
			}
            courser = courser->next;
        }
        cout << endl;
    }


    polynomial operator+(const polynomial& po){
        polynomial result;
        term* p1 = head;
        term* p2 = po.head;

        while (p1 != nullptr|| p2 != nullptr) {
            if (p1 != nullptr && (p2  == nullptr || p1->Exponent > p2->Exponent)) {
                result.addTerm(p1->Coefficent, p1->Exponent);
                p1 = p1->next;
            } else if (p2 != nullptr && (p1 == nullptr || p2->Exponent > p1->Exponent)) {
                result.addTerm(p2->Coefficent, p2->Exponent);
                p2 = p2->next;
            } else {
                result.addTerm(p1->Coefficent + p2->Coefficent, p1->Exponent);
                p1 = p1->next;
                p2 = p2->next;
            }
        }
        return result;
    }
    
    polynomial operator*(const polynomial& po){
        polynomial result;
        for (term* p1 = head; p1 != nullptr; p1 = p1->next) {
            for (term* p2 = po.head; p2 != nullptr; p2 = p2->next) {
                result.addTerm(p1->Coefficent * p2->Coefficent, p1->Exponent + p2->Exponent);
            }
        }
        return result;
    }
};
int main() {
    polynomial p1, p2;


    p1.addTerm(3, 2);
    p1.addTerm(2, 1);
    p1.addTerm(1, 0);

    p2.addTerm(4, 3);
    p2.addTerm(1, 1);
    p2.addTerm(5, 0);

    cout << "P1: "; p1.print();
    cout << "P2: "; p2.print();

    polynomial sum = p1 + p2; 
    cout << "Sum: "; sum.print();

    polynomial product = p1 * p2;
    cout << "Product: "; product.print();

    return 0;
}

