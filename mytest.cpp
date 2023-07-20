/*****************************************
 ** File:    mytest.cpp
 ** Project: CMSC 341 Project 1, Spring 2023
 ** Author:  Oritsejolomisan Mebaghanje
 ** Date:    03/07/23
 ** E-mail:  xz94254@umbc.edu
 **
 ** This file contains the program for mytest.cpp.
 **
 **
 ***********************************************/

#include "fuel.h"
using namespace std;

class Tester{
public:
    FuelSys fuel;
    FuelSys fuel2;
    FuelSys emptyFuel;
    FuelSys fuelTotal;

    //Test to add tank into fuel, returns true.
    bool addTankNormal(){
        bool result = true;
        result = result and (fuel.addTank(1, DEFCAP, 3456));
        result = result and (fuel.addTank(2, DEFCAP, 1234));
        result = result and (fuel.addTank(3, DEFCAP, 5000));
        result = result and (fuel.addTank(4, DEFCAP, 1798));

        return result;
    }

    //Test to add tank error case, returns false
    bool addTankError(){
        bool result = true;
        result = result and (fuel.addTank(1, DEFCAP, 3456));
        result = result and (fuel.addTank(-3, DEFCAP, 1234));
        result = result and (fuel.addTank(3, DEFCAP, 6784));
        result = result and (fuel.addTank(4, DEFCAP, 1798));

        return result;
    }

    //Test to remove tank normal case, returns true
    bool removeTankNormal(){
        bool result = true;
        result = result and (fuel2.addTank(1, DEFCAP, 3456));
        result = result and (fuel2.addTank(2, DEFCAP, 1234));
        result = result and (fuel2.addTank(3, DEFCAP, 6784));
        result = result and (fuel2.addTank(4, DEFCAP, 1798));

        result = result and (fuel2.removeTank(1));
        result = result and (fuel2.removeTank(4));
        result = result and (fuel2.removeTank(3));
        result = result and (fuel.removeTank(2));
        return result;
    }

    //test to remove tank error case, returns false
    bool removeTankError(){
        bool result = true;
        result = result and (fuel2.addTank(1, DEFCAP, 3456));
        result = result and (fuel2.addTank(2, DEFCAP, 1234));
        result = result and (fuel2.addTank(3, DEFCAP, 6784));
        result = result and (fuel2.addTank(4, DEFCAP, 1798));

        result = result and (fuel2.removeTank(-5));
        result = result and (fuel2.removeTank(4));
        result = result and (fuel2.removeTank(3));
        result = result and (fuel.removeTank(2));
        return result;
    }

    //test to find tank normal case, returns true
    bool findTankNormal(){
        bool result = true;
        result = result and (fuel.findTank(3));
        return result;
    }

    //test to find tank error case returns false
    bool findTankError(){
        bool result = true;
        result = result and (fuel.findTank(-9));
        return result;
    }

    //test to return total fuel returns true
    bool totalFuelNormal(){
        bool result = true;
        int curr_fuel = 6000;
        fuelTotal.addTank(1, DEFCAP, 1000);
        fuelTotal.addTank(2, DEFCAP, 2000);
        fuelTotal.addTank(3, DEFCAP, 3000);

        result = result and (curr_fuel == fuelTotal.totalFuel());

        return result;
    }

    //test to return total fuel error case, returns false
    bool totalFuelError(){
        bool result = true;
        result = result and (emptyFuel.totalFuel());

        return result;
    }

    //test to add pump normal case returns true
    bool addPumpNormal(){
        bool result = true;
        result = result and (fuel.addPump(3, 1, 4));
        result = result and (fuel.addPump(3, 2, 4));

        result = result and (fuel.addPump(4, 1, 1));
        result = result and (fuel.addPump(4, 2, 1));

        result = result and (fuel.addPump(1, 1, 3));
        result = result and (fuel.addPump(1, 2, 3));
        //fuel.dumpSys();
        return result;
    }

    //test to add pump error case, returns false
    bool addPumpError1(){
        //adding pump to tank that does not exist
        bool result = true;
        result = result and (fuel.addPump(5, 1, 2));
        result = result and (fuel.addPump(2, 1, 2));
        result = result and (fuel.addPump(2, 1, 2));
        return result;
    }

    //test to add pump error case, returns false
    bool addPumpError2(){
        //adding duplicate pump to tank
        bool result = true;
        result = result and (fuel.addPump(2, 1, 2));
        result = result and (fuel.addPump(2, 1, 2));
        return result;
    }

    //test to remove pump normal case returns true
    bool removePumpNormal(){
        bool result = true;

        result = result and (fuel.removePump(3, 2));
        result = result and (fuel.removePump(4, 1));
        return result;
    }

    //test to remove pump error case returns false
    bool removePumpError1(){
        //removing from non-existing tank
        bool result = true;
        result = result and (fuel.removePump(5, 1));
        result = result and (fuel.removePump(7, 1));
        return result;
    }

    //test to remove pump error case returns false
    bool removePumpError2(){
        //removing from non-existing pump
        bool result = true;
        result = result and (fuel.removePump(3, 4));
        result = result and (fuel.removePump(1, 7));
        return result;
    }

    //test to drain normal case returns true
    bool drainNormalCase(){
        bool result = true;
        //fuel more than space of target tank
        result = result and (fuel.drain(3, 1, 500));
        return result;
    }

    //test to drain error case returns false
    bool drainErrorCase(){
        bool result = true;
        //error case tank does not exist in system
        result = result and (fuel.drain(7, 1, 2402));
        return result;
    }

    //test to fill normal case returns true
    bool TestFillNormal(){
        bool result = true;
        result = result and (fuel.fill(3, 2500));
        return result;
    }

    //test to fill error case returns false
    bool TestFillError(){
        //testing with invalid tank
        bool result = true;
        result = result and (fuel.fill(17, 2500));
        return result;
    }

    //test to make sure overloaded assignment operator works correctly
    bool overloadedassignment(){
        bool result = true;
        FuelSys newFuel;
        newFuel = fuel;
        newFuel.dumpSys();
        cout << "after assignment: " << endl;
        fuel.dumpSys();
        return result;
    }

};

int main(){
    Tester Tester1;
    if(Tester1.addTankNormal()){
        cout << "Test Add tank normal returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Add tank normal returned false" << endl;
    }

    if(Tester1.addTankError()){
        cout << "Test Add tank Error returned true" << endl;
    }
    else{
        cout << "Test Add tank Error returns false, works correctly for error case" << endl;
    }

    if(Tester1.removeTankNormal()){
        cout << "Test Remove tank normal returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Remove tank returns false" << endl;
    }

    if(Tester1.removeTankError()){
        cout << "Test Remove tank Error returned true" << endl;
    }
    else{
        cout << "Test Remove tank Error returns false, works correctly for Error case" << endl;
    }

    if(Tester1.findTankNormal()){
        cout << "Test Find tank Normal returned true, works correctly for Normal case" << endl;
    }
    else{
        cout << "Test Find tank Normal returns false" << endl;
    }

    if(Tester1.findTankError()){
        cout << "Test Find tank Error returned true" << endl;
    }
    else{
        cout << "Test Find tank Error returns false, works correctly for Error case" << endl;
    }

    if(Tester1.totalFuelNormal()){
        cout << "Test Total fuel normal returned true, works correctly for Normal case" << endl;
    }
    else{
        cout << "Test Total fuel normal returned false" << endl;
    }

    if(Tester1.totalFuelError()){
        cout << "Test Total fuel Error returned true" << endl;
    }
    else{
        cout << "Test Total fuel Error returned false, works correctly for Error case" << endl;
    }

    if(Tester1.addPumpNormal()){
        cout << "Test add Pump normal returned true, works correctly for Normal case" << endl;
    }
    else {
        cout << "Test add Pump normal returned false" << endl;
    }

    if(Tester1.addPumpError1()){
        cout << "Test add Pump Error1 returned true" << endl;
    }
    else {
        cout << "Test add Pump Error1 returned false, works correctly for Error case" << endl;
    }

    if(Tester1.addPumpError2()){
        cout << "Test add Pump Error2 returned true" << endl;
    }
    else {
        cout << "Test add Pump Error2 returned false, works correctly for Error case" << endl;
    }

    if(Tester1.removePumpNormal()){
        cout << "Test remove Pump normal returned true, works correctly for Normal case" << endl;
    }
    else {
        cout << "Test remove Pump normal returned false" << endl;
    }

    if(Tester1.removePumpError1()){
        cout << "Test remove Pump Error1 returned true" << endl;
    }
    else {
        cout << "Test remove Pump Error1 returned false, works correctly for Error case" << endl;
    }

    if(Tester1.removePumpError2()){
        cout << "Test remove Pump Error2 returned true" << endl;
    }
    else {
        cout << "Test remove Pump Error2 returned false, works correctly for Error case" << endl;
    }

    if(Tester1.drainNormalCase()){
        cout << "Test drain normal returned true, works correctly for Normal case" << endl;
    }
    else {
        cout << "Test drain normal returned false" << endl;
    }

    if(Tester1.drainErrorCase()){
        cout << "Test drain Error returned true" << endl;
    }
    else{
        cout << "Test drain Error returned false, works correctly for Error case" << endl;
    }

    if(Tester1.TestFillNormal()){
        cout << "Test Fill normal returned true, works correctly for Normal case" << endl;
    }
    else {
        cout << "Test Fill normal returned false" << endl;
    }

    if(Tester1.TestFillError()){
        cout << "Test Fill Error returned true" << endl;
    }
    else {
        cout << "Test Fill Error returned false, works correctly for Error case" << endl;
    }

    if(Tester1.overloadedassignment()){
        cout << "Test overloaded assignment returned true, works correctly" << endl;
    }
    else{
        cout << "Test overloaded assignment returned false" << endl;
    }

}

