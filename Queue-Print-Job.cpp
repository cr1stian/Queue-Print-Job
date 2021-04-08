#include <iostream>

const int MAX_JOBS = 10;

enum class JobStatus{
	Accepted = 0,
	Denied
};

class Job{
private:
	std::string jobName; // Houses job's Alphanumeric Name
	JobStatus status; // Status of job (Accepted, Denied)
	int trackingNumber; // Job's tracking number

public:
	Job(); // Default Constuctor
	Job(std::string name); // One parameter Contructor
	void SetTrackingNum(); // Sets Job's tracking number

	std::string GetName(); // Returns Jobs Name
	JobStatus GetStatus(); // Returns Jobs Status
	int GetTracking(); // Returns Tracking

};

class PrintJobs{
private:
	Job queuedJobs[MAX_JOBS]; // Stores jobs in Queue
	int jobsInQueue; // Quantity of jobs in Queue
	int numExecutedJobs; // Quantity of Executed Jobs
	int numDeniedJobs; // Quantity of Jobs Denied

public:
	PrintJobs(); // Default contructor
	void RequestJob(); // Request a job from user
	void ExecuteJob(); // Executeds a job from Queue
	void DisplayRequestData() const; // Displays records of Jobs completed, denied, in Queue
	bool IsValidName(std::string name) const; // Checks for validity of given name
	bool IsNotFull() const; // Returns true if queue is not full
	char CaptializeChar(char lowerChar); // Returns capitalized char
};

int main(){

	std::cout << "Spaghetti\n";


}

// *** Job Class ***

Job::Job(){
	jobName = "";
	status = JobStatus::Denied;
	trackingNumber = -1;
};

Job::Job(std::string name){
	jobName = name;
}

// Sets Job's Tracking Number using time as the number
void Job::SetTrackingNum(){
	trackingNumber = time(NULL);
}

// Returns Job's Name
std::string Job::GetName(){
	return jobName;
}

// Returns Job's Status
JobStatus Job::GetStatus(){
	return status;
}

// Returns Job's Tracking
int Job::GetTracking(){
	return trackingNumber;
}


// PrintJobs Default contructor
PrintJobs::PrintJobs(){
	jobsInQueue = 0;
	numExecutedJobs = 0;
	numDeniedJobs = 0;
};


// Requests Job data from user
void PrintJobs::RequestJob(){
	std::string jobName;

	std::cout << "Enter Job Name: ";
	std::cin >> jobName;

	if( IsValidName(jobName) && IsNotFull() ){
		Job newJob(jobName);
		queuedJobs[++jobsInQueue] = newJob;
	}
	else if( !IsNotFull() ){
		// throw full error message
	}
	else{
		// throw inValid job name message
	}

}

// Removes the oldest Job on the ueue
void PrintJobs::ExecuteJob(){

}

// Dispays data of Excuted, Denied, Total Requests
void PrintJobs::DisplayRequestData() const{

};

// Checks if string is valid
bool PrintJobs::IsValidName(std::string name)const{
	if( (name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z') ){

	}
	else{
		return false;
	}


}

bool PrintJobs::IsNotFull() const{
	return jobsInQueue < MAX_JOBS - 1;
}


// Capitalizes letter unless a number
char PrintJobs::CaptializeChar(char letter){
	char newChar;

	if(letter >= 'a' && letter <= 'z')
		newChar = letter + 32;

	if(letter >= '0' && letter <= '9')
		newChar = letter;
	
	return newChar;
}