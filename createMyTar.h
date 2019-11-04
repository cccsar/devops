/* writeToDest
 * ----------
 * Writes a string "text" to the file descriptor represented by fd_dest. Since 
 * we are creating a .mytar, it is assumed that fd_dest is asociated with a
 * file opened in append mode. 
 * 
 * 	fd_dest: An integer representing a file descriptor to the file to write.
 * 	text: String containing what will be written.
 * 	size: Size of the string to write.
 *
 */
void writeToDest(int fd_dest, char* text, int size) {	

/* fillField
 * ----------
 * This function calculates the remaining space after inserting a variable
 * size field, and padds it with a special character  == '\2' (by writting) until fitting 
 * a predefined fixed length field. 
 *
 * After that it calls writeToDest to put the field into the .mytar file
 *
 * fixed length fields are : FNAME_LIMIT, FMODE_LIMIT, FSIZE_LIMIT
 *
 *
 * 	fd_dest: file descriptor of the file to write.
 *	content_size:  Size of the field name to write 
 * 	token_field_size:
 */
void fillField(int fd_dest,int content_size, int token_field_size) {

/* setHeadFields
 * ----------
 * Sets the header fields for files. This fields are name, mode and 
 * only for regular files, the size.
 *
 * 	state: state of the file whose attributes are being added to the archive.
 * 	fd_dest: file descriptor of my archive.
 * 	name: Name of the file being processed.
 *
 */
void setHeadFields(int fd_dest, struct stat state, char *name, int is_dir) ;

/* fileWriter
 * ----------
 * Writes from a file to another by using its file descriptors.
 *
 * 	fd_source: file descriptor of the file to write from.
 * 	fd_dest: file descriptor of the file to write.
 *
 */
void fileWriter(int fd_source, int fd_dest) ; 

/* traverseDir
 * ----------
 * Used to traverse a directory tree and write file fields into the archive, 
 * along with * the file content. It does this recursively, in a similar way 
 * to a dfs graph traverse.
 *
 * It does this by, first, avoiding "." and ".." directory entries and 
 * from there it goes by each directory entry, processing it fields (name,
 * permissions, * and size only for regfiles), and copying directories and 
 * regfile metadata to .mytar * as well as regfile content.
 *
 * 	dir: Directory pointer to the dir to traverse.
 * 	dirname: name of the directory to traverse.
 * 	fd: file descriptor of the archive file.
 *
 */
void traverseDir(DIR *dir, char *dirname, int fd) ; 

/* createMyTar
 * --------------
 * Used to create the .mytar file. It beggins setting up the 
 * process creation mask and then it creates the .mytar file.
 *
 * After that it parses every file in the commandline first finding out
 * wether it exists, setting its head field, and then:
 * 	if it is a directory: open it -> traversing it -> on termination it is
 * 		closed
 * 	if it is a regular file: open it -> write it to mytar -> 
 * 		on termination it is closed
 *
 * Requires: 
 * 	access to argv
 *
 */
int main(int argc, char **argv); 

