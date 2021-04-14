#include <iostream>
#include <string>

#define p(x) std::cout << #x << " = " << x << std::endl;

const int MAX_JOBS = 10;

enum JobStatus{
	Accepted = 0,
	Denied
};

enum Menu{
	Quit = 0,
	Request = 1,
	Execute = 2,
	Data = 3
};

class Job{
private:
	std::string name; // Houses job's Alphanumeric Name
	JobStatus status; // Status of job (Accepted, Denied)
	int trackingNumber; // Job's tracking number

public:
	Job(); // Default Constuctor
	void SetName(std::string name); // One parameter Contructor
	void SetTrackingNum(); // Sets Job's tracking number
	void SetStatus(JobStatus newStatus); // Sets Job's status

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
	std::string CaptializeStr(std::string lowerStr); // Returns capitalized String

	int Menu(); // Displays Menu
};

int main(){



	int MenuOption = -1;

	PrintJobs newPrinter;

	MenuOption = newPrinter.Menu();
	
	while( MenuOption != Menu::Quit){
		switch( MenuOption ){
			case 1:
				newPrinter.RequestJob();
				break;
			case 2:
				newPrinter.ExecuteJob();
				break;
			case 3:
				newPrinter.DisplayRequestData();
				break;
			default:
				std::cout << "Error Ocurred\n";
				break;
		}
		MenuOption = newPrinter.Menu();
	
	}




	/*
	PrintJobs newInstance;
	Job newJob;
	std::cout << newJob.GetName();
	newJob.SetTrackingNum();
	std::cout << "\n" << newJob.GetTracking();

	std::string name = "crIst1an H";

	std::cout << "\n" << newInstance.IsValidName(name);
	std::cout << "\n" << newInstance.CaptializeStr(name);
	std::cout << "\n" << name;


	newInstance.RequestJob();
	newInstance.DisplayRequestData();
	*/
}

// *** Job Class ***

// Default constructor
Job::Job(){
	name = "";
	status = JobStatus::Denied;
	trackingNumber = -1;
};

// Constructor with Name Parameter
void Job::SetName(std::string jobName){
	name = jobName;
}

// Sets Job's Tracking Number using time as the number
void Job::SetTrackingNum(){
	trackingNumber = time(NULL);
}

// Sets Job's Status by the given bool value
void Job::SetStatus(JobStatus newStatus){
	status = newStatus;
}

// Returns Job's Name
std::string Job::GetName(){
	return name;
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
	std::string jobName = "";
	std::string confirmation = "";

	Job newJob;

	if( IsNotFull() ){
		std::cout << "Enter Job Name: ";
		std::cin >> jobName;

		if( IsValidName(jobName) ){
			newJob.SetName(jobName);
			newJob.SetTrackingNum();
			newJob.SetStatus(JobStatus::Accepted);

			queuedJobs[++jobsInQueue] = newJob;

			confirmation = "Job Status: Accepted \nTracking #: " + std::to_string(newJob.GetTracking()) + " \nPosition in Queue: " + std::to_string(jobsInQueue);
		}
		else{
			confirmation = "Job Status: Denied\nReason: Invalid Name";
			numDeniedJobs++;
		}
	}
	else{
		confirmation = "Job Status: Denied\nReason: Print Queue is Full";
		numDeniedJobs++;
	}

	std::cout << confirmation;
}

// Removes the oldest Job on the ueue
void PrintJobs::ExecuteJob(){

}

// Dispays data of Excuted, Denied, Total Requests
void PrintJobs::DisplayRequestData() const{
	std::cout << "\n**JOBS DATA**\n"
		<< "# of Prints Requested: " << numExecutedJobs + numDeniedJobs + jobsInQueue << "\n"
		<< "# of Prints Executed: " << numExecutedJobs << "\n"
		<< "# of Prints in Queue: " << jobsInQueue << "\n"
		<< "# of Prints Denied: " << numDeniedJobs << "\n";
};

// Checks if string is valid
bool PrintJobs::IsValidName(std::string name)const{
	bool isValid = true;

	if( (name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z') ){ // Checking First char
		for( int pos(0); pos < name.length(); pos++ ){
			if( (name[pos] >= 'a' && name[pos] <= 'z') || name[pos] == ' ' ){
				isValid = true;
			}
			else if( name[pos] >= 'A' && name[pos] <= 'Z' ){
				isValid = true;
			}
			else if( name[pos] >= '0' && name[pos] <= '9' ){
				isValid = true;
			}
			else{
				isValid = false;
				pos = name.length();
			}
		}
	}
	else{
		isValid = false;
	}
	return isValid;
}

bool PrintJobs::IsNotFull() const{
	return jobsInQueue < MAX_JOBS - 1;
}


// Capitalizes letter unless a number
std::string PrintJobs::CaptializeStr(std::string lowerStr){
	std::string newStr("");

	for( char letter : lowerStr )
		newStr += toupper(letter);

	return newStr;
}

int PrintJobs::Menu(){
	int choice = -1;

	std::cout
		<< "**Menu**\n"
		<< "0 Quit\n"
		<< "1 Request Print\n"
		<< "2 Execute Print\n"
		<< "3 Display Print Data\n"
		<< ": ";

	std::cin >> choice;

	if(std::cin.fail() || (choice < 0 || choice > 3) ){
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		choice = -1;
	}

	return choice;
}