
/*
   Name: Tirth Patel
   CS-251 UIC 
   Project 1 
   
   This is a spam filter program which loads, checks, displays and filters
   non-spam emails from a given spamlist.
   
 */
#include <iostream>
#include <string>   
#include <fstream>

#include "ourvector.h"
using namespace std;


/*
Load function which takes in filename and the spam vector as parameters 
to read the user-input spamlist file and store the emails
into  a vector
*/
void performCommandload(string filename, ourvector<string>& spamVec)
{
	spamVec.clear();   // clear the spam list before second load command
	string value;
	ifstream infile(filename);
			
	if(!infile.good())
	{
		cout<<" **Error, unable to open '"<<filename<<"'"<<endl;
		return;
		
	}
	
	cout<<" Loading "<<"'"<<filename<<"'"<<endl;
	
	
	infile>>value;
	
	while(!infile.eof())
	{
		spamVec.push_back(value);     // push the emails into the vector spamVec
		infile>>value;
	}
	cout << "# of spam entries: "<<spamVec.size()<<endl;
}


/*
 binarySearch function to check wheter the user entered email is a spam or not.
 return type : boolean. 
 Returns true if the email is spam and false if not.
 Parameters : username and domain of the user input email and spamVector
 
 */
bool binarySearch(string username, string domain, ourvector<string>& spamVector)
{

	int low =0;
	int high = spamVector.size()-1;
	int mid;

	while(high >= low)
	{
 	   mid = low + (high - low)/2 ;
	   string midEmail = spamVector[mid];  // get the middle email from the loaded spam vector
		
	   string midUsername = midEmail.substr(midEmail.find(':')+1); // get the username of middle email (after ":")
		
	   string midDomain = midEmail.substr(0,midEmail.find(':'));  // get domain of the middle email 

		if(midDomain < domain)
		{
			low = mid +1;
		}
		else if (midDomain > domain)
		{
			high = mid -1;
		}
		else if(midDomain == domain)  // when midDomain is equal to domain.. check for username
		{

			if(midUsername < username)
			{
				low = mid + 1;
			}
			 else if (midUsername > username)
			{
				high = mid -1;
			} 
			else                    // when username is equal to midUsername
				return true;
			
		}
	
}
	return false;
}

/*
performCommandcheck to check if the email is a spam or not
Paramters : user input email and spam vector

*/
void performCommandcheck( string email, ourvector<string>& spamVector)
{
	string username = email.substr(0,email.find('@'));  // get the username of the input email to check 
	string domain = email.substr(email.find('@') + 1);  // get the domain of the input email to check 
	
	// call binary search to check if an email is spam or not 
	if(binarySearch(username,domain,spamVector)==true || binarySearch("*",domain,spamVector)==true)
	{
		cout<<" "<<email<<" is spam"<<endl;
		
	}
	else {
		cout<<" "<<email<<" is not spam"<<endl;
	}
	
}

/*
 performCommandfilter function to filter the emails list file and output 
 the non spam emails to an output file
 Parameters : filename (to filter from), output file name, and spamvector
 
 */
void performCommandfilter(string filename, string outFileName, ourvector<string>& spamVector)
{
	ifstream infile(filename);
	ofstream outfile(outFileName);
	int msgId;                   
	string email;
	string subject;
	int nonspam = 0;   // to keep track of number of non spam emails
	int emailprocessed=0;  // to keep track of total number of emails processed
	if(!infile.good())
	{
		cout<<" **Error, unable to open '"<<filename<<"'"<<endl;
		return;
		
	}
	
	infile>> msgId;
	while(!infile.eof())
	{
		infile >> email;
		getline(infile,subject);

		string username = email.substr(0,email.find('@'));
		string domain = email.substr(email.find('@') + 1);
 		emailprocessed++;                           // counter to get total emails processed 

		if((binarySearch(username,domain,spamVector)== false) ) // calling binary search to check if email is non spam
		{
			if(binarySearch("*",domain,spamVector)==false){
			nonspam++;   
			
			outfile<<msgId<<" "<<email<<subject<<endl;   // output the msg id email and subject to out file
		}
		}
		

		infile >>msgId;
		
	}
	cout <<" # emails processed: "<<emailprocessed<<endl;
	cout<<"# non-spam emails:  "<<nonspam<<endl;
	
}

/*
 display function to loop through the spam vector and display
 each email
 parameter : spam vector
 */
void display (ourvector<string>& spamVec)
{
	for(auto spamEmail : spamVec )   // loop through the loaded spam vector and print all the emails
	{
		cout << spamEmail<<endl;
	}
	
}

int main()
	
{
	
	string userInput;
	ourvector<string> spamVector;
	string filename;  // emails files
	string email; // for check and filter command
	string subject;// for filter command
	string outFileName; // for filter command to output in output file
	
	cout << "** Welcome to spam filtering app **"<<endl<<endl;
    cout<<"Enter command or # to exit>";
	cin>>userInput;
	
	while(userInput !="#"){
	
		if(userInput == "load")  // call performCommandload
		{  	

			cin >> filename;
			performCommandload( filename, spamVector); 
			
		}

		else if(userInput=="display" )  
		{
			cout<<" ";
			display(spamVector);// calling display fuaction  to display loaded spam vector
          
		}
		
		else if (userInput == "check")   // call performCommandcheck
		{
			cin >> email;
 			performCommandcheck( email, spamVector);  
			 
		}
		
		else if(userInput == "filter") // call performCommandfilter
		{
			cin>>filename;
			cin>>outFileName;
 			performCommandfilter( filename,outFileName, spamVector);

		}
		else
		{
			cout<<" **invalid command"<<endl;
		} 
		cout << endl;
		cout<<"Enter command or # to exit>";
		cin >> userInput;

		
	}
	
	
}

//End