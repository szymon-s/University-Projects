package pl.polsl.Model;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/**
 * Class which provide test methods for class Model
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class ModelTest {

    private Model model;

    /**
     * Test if method throws proper exceptions, if there is no file, or file has
     * bad content.
     *
     * @param filename file name passed by the parameter, different files has
     * different values inside.
     */
    @ParameterizedTest
    @ValueSource(strings = {"correct_file.txt",
        "bad_content_file.txt", "empty_file.txt", "file_no_exists"})
    public void testLoadDataException(String filename) {
        model = new Model(filename, "QuickSort");
        try {
            model.loadData();
            if (filename.equals("bad_content_file.txt")
                    || filename.equals("empty_file.txt") || filename.equals("file_no_exists")) {
                fail("An exception should be thrown!");
            }
        } catch (IOException | EmptyFileException e) {
        }
    }

    /**
     * Test if data loaded is the same as data in the file.
     *
     * @param filename file name passed by the parameter, different files has
     * different values inside.
     */
    @ParameterizedTest
    @ValueSource(strings = {"zero_values_file.txt",
        "negative_values_file.txt", "positive_values_file.txt"})
    public void testLoadDataValues(String filename) {
        model = new Model(filename, "QuickSort");
        try {
            model.loadData();
            if (filename.equals("zero_values_file.txt")) {
                ArrayList<Double> zeroArray = new ArrayList<>(
                        Arrays.asList(0.0, 0.0, 0.0, 0.0, 0.0));
                assertTrue(zeroArray.equals(model.getData()),
                        "Loaded data is incorrect!");
            }
            if (filename.equals("negative_values_file.txt")) {
                ArrayList<Double> negativeArray = new ArrayList<>(
                        Arrays.asList(-54.0, -2.3, -5.21, -24.5));
                assertTrue(negativeArray.equals(model.getData()),
                        "Loaded data is incorrect!");
            }
            if (filename.equals("positive_values_file.txt")) {
                ArrayList<Double> positiveArray = new ArrayList<>(
                        Arrays.asList(5.0, 5.3, 12.0, 43.5));
                assertTrue(positiveArray.equals(model.getData()),
                        "Loaded data is incorrect!");
            }

        } catch (IOException | EmptyFileException e) {
        }
    }
}
