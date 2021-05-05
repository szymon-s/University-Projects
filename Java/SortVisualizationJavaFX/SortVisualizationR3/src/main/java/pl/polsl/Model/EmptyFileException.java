package pl.polsl.Model;

/**
 * Exception which is thrown when file has no data or the data is incorrect.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class EmptyFileException extends Exception {

    public EmptyFileException() {
    }

    public EmptyFileException(String message) {
        super(message);
    }
}
