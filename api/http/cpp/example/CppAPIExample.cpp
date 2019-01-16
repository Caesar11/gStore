/*=============================================================================
# Filename: CppAPIExample.cpp
# Author: Bookug Lobert 
# Mail: 1181955272@qq.com
# Last Modified: 2016-02-21 21:32
# Description: originally written by hanshuo, modified by zengli
=============================================================================*/

#include "GstoreConnector.h"
#include <string>
#include <iostream>

using namespace std;

// before you run this example, make sure that you have started up ghttp service (using bin/ghttp db_name port)
int main(int argc, char * argv[])
{
    string username = "root";
    string password = "123456";

    // initialize the GStore server's IP address and port.
    cout << "in" <<endl;
    GstoreConnector gc("172.31.222.94", 9000);
    cout << "out"<<endl;
    // build a new database by a RDF file.
    // note that the relative path is related to gserver
	
	gc.build("lubm", "data/lubm/lubm.nt", username, password);
   
	//load the database that you've build.
	gc.load("lubm", username, password);
    // then you can execute SPARQL query on this database.
    std::string sparql = "select ?x where \
                         { \
                         ?x    <rdf:type>    <ub:UndergraduateStudent>. \
                         ?y    <ub:name> <Course1>. \
                         ?x    <ub:takesCourse>  ?y. \
                         ?z    <ub:teacherOf>    ?y. \
                         ?z    <ub:name> <FullProfessor1>. \
                         ?z    <ub:worksFor>    ?w. \
                         ?w    <ub:name>    <Department0>. \
                         }";

    std::string answer = gc.query(username, password, "lubm", sparql);
    std::cout << answer << std::endl;
    
    // make a SPARQL query and save the result in ans.txt
    gc.query(username, password, "lubm", sparql, "ans.txt");

    // unload this database.
    gc.unload("lubm", username, password);
    // also, you can load some exist database directly and then query.
    gc.load("lubm", username, password);
    answer = gc.query(username, password, "lubm", sparql);
    std::cout << answer << std::endl;

	//you can monitor a database
	answer = gc.monitor("lubm", username, password);
	std::cout << answer << std::endl;

	//add a user(with username: Jack, password: 2)
	answer = gc.user("add_user", username, password, "Jack", "2");
	std::cout << answer << std::endl;
		
	//add privilege to user Jack(add_query, add_load, add_unload)
	answer = gc.user("add_query", username, password, "Jack", "lubm");
	std::cout << answer << std::endl;
		
	//then Jack can query the database LUBM10
	answer = gc.query("Jack", "2", "lubm", sparql);
	std::cout << answer << std::endl;
		
	//delete privilege of user Jack(delete_query, delete_load, delete_unload)
	answer = gc.user("delete_query", username, password, "Jack", "lubm");
	std::cout << answer << std::endl;
	
	//delete user(with username: Jack, password: 2)
	answer = gc.user("delete_user", username, password, "Jack", "2");
	std::cout << answer << std::endl;

	gc.unload("lubm", username, password);
    
    return 0;
}

