/* fileWriter2
 * ----------
 * Writes from a file to another by using its file descriptors. It optionally
 * writes up to 'total' characters, depending on wether the flag bounded is set.
 *
 * 	fd_source: file descriptor of the file to write from.
 * 	fd_dest: file descriptor of the file to write.
 *
 */
void fileWriter(int fd_source, int fd_dest, int total) ; 

/* getFieldSize
 * --------------
 *  It reads from the begginning of a field, until the first occurrence of
 *   character, then it returns its size
 *
 * On termination it accommodates file offset for propper writting (on floor)
 *
 * 	fd_orig: file descriptor of the .mytar file
 * 	roof: offset of the .mytar file that matches the end of a field.
 * 	floor: offset of the .mytar file that matches the beggining of a field.
 *
 */
off_t getFieldSize(int fd_orig, int roof,int floor) {

/* getField
 * --------------
 * Given a file descriptor and two offset from a .mytar file, it gets
 * the field bounded by roof and floor and returns it as a character
 * for further processing (creating directories, files, and setting 
 * permissions)
 *
 * 	fd: file descriptor of mytar file. 
 * 	roof: offset of the field upper bound. 
 * 	floor: offset of the field lower bound. 
 *
 */
char *getField(int fd, int roof, int floor) ;

/* extractMytar
 * --------------
 * It receives a .mytar file and extracts it to current path. It uses 
 * file offsets to extract fields and content from .mytar file. 
 *
 * First it receives the name of the .mytar file. If it exists, it starts 
 * parsing its fields. 
 *
 */
int main (int argc, char **argv) ;  			//extract file
	

