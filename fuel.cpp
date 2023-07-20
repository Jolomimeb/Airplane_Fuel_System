#include "fuel.h"

FuelSys::FuelSys() {
  //sets m_current to nullptr
    m_current = nullptr;
}

FuelSys::~FuelSys() {
  //calls the clear function which is a helper function that clears the tanks and pump
    if (m_current == nullptr){
        return;
    }
    clear();
}

bool FuelSys::addTank(int tankID, int tankCap, int tankFuel = 0) {
  //returns false if the tankId is not found
    if (findTank(tankID)){
        return false;
    }
    //checks if the list is empty and then creates a new tank
    else {
        Tank *myTank = new Tank(tankID, tankCap, tankFuel);
        if (m_current){
            myTank->m_next = m_current->m_next;
            m_current->m_next = myTank;
        }
        else{
            myTank->m_next = myTank;
        }
        m_current = myTank;
        return true;
    }
}

bool FuelSys::removeTank(int tankID) {
  //checks to see if m_current is null
    if (m_current == nullptr){
        return false;
    }
    else{
      //creates two temp variable used to traverse and delete current tanks
        Tank* tempTank = m_current->m_next;
        Tank* prev = m_current;

        //removing first element
        if (tempTank->m_tankID == tankID) {
            prev->m_next = tempTank->m_next;
            delete tempTank;
            return true;

        }
        prev = m_current->m_next;
        tempTank = prev->m_next;
	
        //traversing through tempTank to find the specific tank to remove
        while (tempTank != m_current->m_next) {
            if (tempTank->m_tankID == tankID) {
                prev->m_next = tempTank->m_next;
                if (tempTank == m_current) {
                    m_current = prev;
                }
                delete tempTank;
                return true;
            }
            prev = tempTank;
            tempTank = tempTank->m_next;
        }
        return false;
    }
}

bool FuelSys::findTank(int tankID) {
  
    if(m_current){
      //checks if the tank ID equals m_tankID and returns true if it does
        Tank* tempTank = m_current->m_next;
        if (tankID == m_current->m_tankID){
            return true;
        }
	//iterates over the tank to find the specific ID and returns true if it finds it
        Tank* prevTank = m_current;
        while (tempTank != m_current) {
            if (tempTank->m_tankID == tankID) {
                m_current = prevTank;
                return true;
            }
            tempTank = tempTank->m_next;
            prevTank = tempTank;
        }

    }
    return false;
}

bool FuelSys::addPump(int tankID, int pumpID, int targetTank) {
  
    bool myBool = true;
    Tank* tempTank = m_current->m_next;
    if (!findTank(tankID)){
        return false;
    }
    //iterates over the tank and check if the tank ID equals m_tankID and then creates a new pump to the tank and returns true
    while (m_current != nullptr && (tempTank != m_current->m_next or myBool)) {
        if (tankID == tempTank->m_tankID){
            Pump* newPump = new Pump(pumpID, targetTank);
            newPump->m_next = tempTank->m_numPumps;
            tempTank->m_numPumps = newPump;
            return true;
        }
        if (tempTank == m_current){
            myBool = false;
        }
        tempTank = tempTank->m_next;
    }
    return false;

}

bool FuelSys::removePump(int tankID, int pumpID) {
  //iterates over tanks and pumps and finds the pump with the specific ID and deletes it from the tank
    Tank* tempTank = m_current->m_next;
    while (m_current != nullptr && tempTank != m_current){
        if (tempTank->m_tankID == tankID) {
            Pump* currentPump = tempTank->m_numPumps;
            Pump* prev = nullptr;
            while (currentPump != nullptr){
                if (currentPump->m_pumpID == pumpID) {
                    if (prev == nullptr) {
                        tempTank->m_numPumps = currentPump->m_next;
                    }
                    else {
                        prev->m_next = currentPump->m_next;
                    }

                    delete currentPump;
                    return true;
                }
                prev = currentPump;
                currentPump = currentPump->m_next;
            }
        }
        tempTank = tempTank->m_next;
    }

    return false;
}

int FuelSys::totalFuel() const {
    Tank* temp = m_current;
    int total = 0;
    //checks if m_current is null
    if (m_current == nullptr){
        return 0;
    }
    //Iterates over m_currrent and adds up the tankfuel and returns the amount
    do{
        total += temp->m_tankFuel;
        temp = temp->m_next;
    }while (temp != m_current);
    return total;

}


bool FuelSys::drain(int tankID, int pumpID, int fuel) {
    Tank* sourceTank = m_current->m_next;
    Tank* targetTank;
    while(sourceTank != m_current){
        //find tank with the specified ID
        if (sourceTank->m_tankID == tankID){
            //finds the pump
            Pump* tempPump = sourceTank->m_numPumps;
            //iterate over the pump
            while(tempPump != nullptr){
	      //checks if the pump ID equals m_pumpID
                if(tempPump->m_pumpID == pumpID){
                    targetTank = sourceTank->m_next;

                    while (targetTank != sourceTank){
		      //calculates the empty space in the tank
                        int emptySpace = targetTank->m_tankCapacity - targetTank->m_tankFuel;
			//checks if the fuel is more than the empty space and then adds up the empty space
                        if (fuel > emptySpace){
                            targetTank->m_tankFuel += emptySpace;
                            //return true;
                        }
                        else if (fuel < emptySpace){
                            targetTank->m_tankFuel += fuel;
			    //checks if the source tank is more than or equal to the fuel and then removes the amount of fuel taken
                            if (sourceTank->m_tankFuel >= fuel) {
                                sourceTank->m_tankFuel -= fuel;
                            } else {
                                sourceTank->m_tankFuel = 0;
                            }

                            return true;
                        }
                        targetTank = targetTank->m_next;
                    }
                    return false;

                }
                tempPump = tempPump->m_next;
            }
            return false;
        }

        sourceTank = sourceTank->m_next;
    }

    return false;
}

bool FuelSys::fill(int tankID, int fuel) {
    Tank* tempTank = m_current->m_next;
    //Iterates over the tank and finds the tank with the specific ID
    while (tempTank != m_current) {
        if (tempTank->m_tankID == tankID) {
	  //calculates the tankspace
            int TankSpace = tempTank->m_tankCapacity - tempTank->m_tankFuel;
	    //checks if the tankspace is less than the fuel ad adds up the space
            if (TankSpace < fuel) {
                tempTank->m_tankFuel += TankSpace;
                return true;
            }
	    //checks if the tankspace is greater than the fuel and adds up the fuel
            else if (TankSpace >= fuel) {
                tempTank->m_tankFuel += fuel;
                return true;
            }

        }
        tempTank = tempTank->m_next;
    }

    return false;
}

const FuelSys& FuelSys::operator=(const FuelSys& rhs) {
  //checks for self assignment
  if (&rhs != this){
    //clears the current tank and pumps
        if (m_current != nullptr) {
            clear();
        }
	
        if (rhs.m_current != nullptr){
            Tank* initTank = rhs.m_current;
            Tank* currTank = initTank;
            do{
                currTank = currTank->m_next;
                addTank(currTank->m_tankID, currTank->m_tankCapacity, currTank->m_tankFuel);

                Pump* initPump = nullptr;
                Pump* currPump = currTank->m_numPumps;
                Pump* newPump = nullptr;
		//goes through the pump and performs the assignment
                while(currPump != nullptr){
                    newPump = new Pump(currPump->m_pumpID, currPump->m_target, nullptr);
                    if (initPump != nullptr){
                        initPump->m_next = newPump;
                    }else{
                        m_current->m_numPumps = newPump;
                    }
                    initPump = newPump;
                    currPump = currPump->m_next;
                }
            }while(currTank->m_tankID != initTank->m_tankID);

        }
    }
    return *this;
}



void FuelSys::dumpSys() const {
    if (m_current != nullptr) {
        Tank* tempTank = m_current->m_next;//we start at front item
        //we continue visting nodes until we reach the cursor
        while (m_current != nullptr && tempTank != m_current) {
            cout << "Tank " << tempTank->m_tankID << "(" << tempTank->m_tankFuel << " kg)" << endl;
            // now dump the targets for all pumps in this tank
            // we need to traverse the list of pumps
            dumpPumps(tempTank->m_numPumps);
            tempTank = tempTank->m_next;
        }
        //at the end we visit the cursor (current)
        //this also covers the case that there is only one item
        cout << "Tank " << m_current->m_tankID << "(" << m_current->m_tankFuel << " kg)" << endl;
        dumpPumps(tempTank->m_numPumps);
        cout << "The current tank is " << m_current->m_tankID << endl;
    }
    else
        cout << "There is no tank in the system!\n\n";
}

void FuelSys::dumpPumps(Pump* pumps) const {
    // this traverses the linked list to the end
    Pump* tempPump = pumps;
    while (tempPump != nullptr) {
        cout << " => pump " << tempPump->m_pumpID << "(To tank " << tempPump->m_target << ")" << endl;
        tempPump = tempPump->m_next;
    }
}

