package pl.polsl.Model;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Class which provides test methods for class SelectionSort
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class SelectionSortTest {

    /**
     * Interface which can be implemented by different sort algorithms, virtual
     * method sort of this interface will be tested.
     */
    private SortAlgorithm sortAlgorithm;

    /**
     * ArrayList needed to call sort method.
     */
    private List<List<Double>> sortSteps;

    /**
     * Method which prepare proper sort algorithm and inicialize ArrayList.
     */
    @BeforeEach
    public void setUp() {
        sortAlgorithm = new SelectionSort();
        sortSteps = new ArrayList<>();
    }

    /**
     * Test if SelectionSort algorithm final results are correct for zero
     * values.
     */
    @Test
    public void testSortZeroValues() {
        List<Double> testArray = new ArrayList<>(
                Arrays.asList(0.0, 0.0, 0.0, 0.0, 0.0));
        List<Double> sortedArray = new ArrayList<>(
                Arrays.asList(0.0, 0.0, 0.0, 0.0, 0.0));
        sortAlgorithm.sort(testArray, sortSteps);
        assertTrue(testArray.equals(sortedArray), "Sort result is wrong!");
    }

    /**
     * Test if SelectionSort algorithm final results are correct for negative
     * values.
     */
    @Test
    public void testSortNegativeValues() {
        List<Double> testArray = new ArrayList<>(
                Arrays.asList(-5.2, -21.1, -2.4, -2.3, -42.3));
        List<Double> sortedArray = new ArrayList<>(
                Arrays.asList(-42.3, -21.1, -5.2, -2.4, -2.3));
        sortAlgorithm.sort(testArray, sortSteps);
        assertTrue(testArray.equals(sortedArray), "Sort result is wrong!");
    }

    /**
     * Test if SelectionSort algorithm final results are correct for positive
     * values.
     */
    @Test
    public void testSortPositiveValues() {
        List<Double> testArray = new ArrayList<>(Arrays.asList(5.2, 21.1, 2.4, 2.3, 42.3));
        List<Double> sortedArray = new ArrayList<>(Arrays.asList(2.3, 2.4, 5.2, 21.1, 42.3));
        sortAlgorithm.sort(testArray, sortSteps);
        assertTrue(testArray.equals(sortedArray), "Sort result is wrong!");
    }

    /**
     * Test if SelectionSort algorithm final results are correct for mixed
     * values.
     */
    @Test
    public void testSortMixedValues() {
        List<Double> testArray = new ArrayList<>(Arrays.asList(-5.2, 21.1, -2.4, 2.3, -42.3));
        List<Double> sortedArray = new ArrayList<>(Arrays.asList(-42.3, -5.2, -2.4, 2.3, 21.1));
        sortAlgorithm.sort(testArray, sortSteps);
        assertTrue(testArray.equals(sortedArray), "Sort result is wrong!");
    }
}
