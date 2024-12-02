### **Simple Version Control System (VCS)**

This project implements a basic version control system, inspired by Git, to help manage file changes and maintain a repository. It includes features for initializing a repository, staging files, committing changes, viewing logs, and interacting with a remote server.

---

### **Features**

1. **Repository Initialization**:

   - Create a `.vcs` directory structure to store staging and commit data.
   - Sets up the initial `HEAD` file for branch tracking.

2. **Staging Files**:

   - Add files to a staging area for tracking.

3. **Committing Changes**:

   - Save changes from the staging area to the repository.
   - Automatically timestamps commits and stores messages.

4. **Viewing Commit Logs**:

   - View a list of previous commits and their messages.

5. **Remote Interaction**:

   - **Push**: Send repository data to a remote server.
   - **Fetch**: Retrieve repository data from a remote server.

6. **Set Origin**:
   - Configure the remote server address for easier interaction.

---

### **Getting Started**

#### **Requirements**

- **Windows**:
  - GCC (MinGW or other distributions)
  - Winsock2 library (included in standard Windows development tools)
- **Linux**:
  - GCC or any C compiler
  - Standard libraries for networking (`arpa/inet.h`, `sys/socket.h`)

#### **Installation**

1. Clone or download this repository.
2. Build the project using the `Makefile`:
   ```bash
   make
   ```
3. The executable `vcs` (or `vcs.exe` on Windows) will be created.

---

### **Usage**

#### **Basic Commands**

- **Initialize Repository**:

  ```bash
  ./vcs init
  ```

  Creates a `.vcs` directory in the current folder.

- **Add Files**:

  ```bash
  ./vcs add <filename>
  ```

  Stages a file for the next commit.

- **Commit Changes**:

  ```bash
  ./vcs commit -m "<message>"
  ```

  Saves the staged changes to the repository with a message.

- **View Logs**:
  ```bash
  ./vcs log
  ```
  Displays all commits and their messages.

#### **Remote Commands**

- **Set Remote Origin**:

  ```bash
  ./vcs set-origin <url>
  ```

  Saves the server address for remote interactions.

- **Push to Server**:

  ```bash
  ./vcs push <server_ip> <port>
  ```

  Sends the repository data to the specified server.

- **Fetch from Server**:
  ```bash
  ./vcs fetch <server_ip> <port>
  ```
  Retrieves repository data from the specified server.

---

### **Directory Structure**

```
.vcs/
├── HEAD              # Tracks the current branch
├── staging/          # Staging area for changes
├── commits/          # Directory containing commit history
│   └── <timestamp>/  # Each commit stored by timestamp
│       ├── files/    # Files committed in this snapshot
│       └── message.txt # Commit message
```

---

### **Contributing**

Feel free to submit issues, fork the project, or contribute via pull requests.

---

### **License**

This project is open-source and distributed under the Apache License.
