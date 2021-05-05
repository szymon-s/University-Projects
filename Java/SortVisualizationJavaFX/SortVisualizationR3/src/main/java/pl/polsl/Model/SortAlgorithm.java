package pl.polsl.Model;

import java.util.List;

/**
 * SortAlgorithm interface with sort method which is used for implementation of
 * different sort algotihms.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public interface SortAlgorithm {

    /**
     * Method which has to be implemented by sort algorithm, it's used to sort
     * the List of Double values.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     */
    public void sort(List<Double> data, List<List<Double>> sortedData);
}
