package pl.polsl.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import pl.polsl.Model.Model;

/**
 * Servlet which handle sorting the data and sending result of the operation to
 * the client.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
@WebServlet(name = "SortData", urlPatterns = {"/SortData"})
public class SortDataServlet extends HttpServlet {

    private Model model;

    /**
     * Use SortAlgorithm stored in Model to sort the data.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores sort steps.
     */
    private void sortData(List<Double> data, List<List<Double>> sortedData) {
        this.model.getSortAlgorithm().sort(data, sortedData);
    }

    /**
     * Get data from the Model.
     *
     * @return List of Double values.
     */
    private List<Double> getModelsData() {
        return this.model.getData();
    }

    /**
     * Get List with sort steps.
     *
     * @return List of Lists of Double values which stores all sorting steps.
     */
    private List<List<Double>> getSortedData() {
        return this.model.getSortingSteps();
    }

    /**
     * Get sortName from Model.
     *
     * @return name of sort algorithm.
     */
    private String getModelsSortName() {
        return this.model.getSortName();
    }

    /**
     * Set sortName to the model.
     *
     * @param sortName name of sort algorithm.
     */
    private void setModelsSortName(String sortName) {
        this.model.setSortName(sortName);
    }

    /**
     * Handles the HTTP <code>GET</code> method which sorts data stored in the
     * model and sends result of the operation to the client.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        model = (Model) request.getSession().getAttribute("model");
        String htmlCode = "<!DOCTYPE html>\n"
                + "<html>\n"
                + "    <head>\n"
                + "        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n"
                + "        <title>Sort Visualization</title>\n"
                + "    </head>\n"
                + "    <body style=\"text-align:center; padding: 10% 0;\">\n"
                + "        <div style=\" overflow: auto; height:auto; border: 3px solid black; margin: auto; width: 50%;background-color: #a6faff;\"> ";
        response.setContentType("text/html; charset=UTF-8");
        PrintWriter out = response.getWriter();

        if (model != null && getModelsData() != null) {
            getSortedData().clear();
            setModelsSortName(request.getParameter("SortAlgorithm"));
            List<Double> data = new ArrayList<>(getModelsData());
            sortData(data, getSortedData());
            Cookie isSortedCookie = new Cookie("isSorted", "true"); //sort visualization can be shown only when sorting is done
            response.addCookie(isSortedCookie);
            htmlCode += "Data sorted using algorithm: " + getModelsSortName();
        } else {
            htmlCode += "Load the data before sorting!";
        }
        htmlCode += "</div>"
                + "<br/><br/>"
                + "<form action=\"index.html\">"
                + "<input type=\"submit\" value=\"Back\"/>"
                + "</form>"
                + "</body>"
                + "</html>";
        out.print(htmlCode);
    }
}
