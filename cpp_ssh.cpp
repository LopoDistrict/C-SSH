#include <libssh/libssh.h> // sudo apt-get install libssh-dev
#include <iostream> 
#include <stdexcept> 
 
void connectSSH(const std::string& host, const std::string& user, const std::string& pass) { 
    ssh_session session = ssh_new(); 
    if (session == nullptr) { 
        throw std::runtime_error("Error: creating the SSH session"); 
    } 
 
    //options
    ssh_options_set(session, SSH_OPTIONS_HOST, host.c_str()); 
    ssh_options_set(session, SSH_OPTIONS_USER, user.c_str()); 
 
    // server connections 
    if (ssh_connect(session) != SSH_OK) { 
        std::cerr << "Error: unable to  connect to host: " << ssh_get_error(session) << std::endl; 
        ssh_free(session); 
        return; 
    } 
 
    // password
    if (ssh_userauth_password(session, nullptr, pass.c_str()) != SSH_AUTH_SUCCESS) { 
        std::cerr << "Error: Wrong password: " << ssh_get_error(session) << std::endl; 
        ssh_disconnect(session); 
        ssh_free(session); 
        return; 
    } 
 
    std::cout << "SSH sucessfully established" << std::endl; 
 
    
    ssh_disconnect(session); 
    ssh_free(session); 
} 
 
int main() { 
    //main function to connect
    std::string host = "your.server.com" // or ip adress; 
    std::string user = "username"; // you need to change those values
    std::string password = "password"; 
 
    try { 
        connectSSH(host, user, password); 
    } catch (const std::exception& e) { 
        std::cerr << e.what() << std::endl; 
    } 
 
    return 0; 
} 
