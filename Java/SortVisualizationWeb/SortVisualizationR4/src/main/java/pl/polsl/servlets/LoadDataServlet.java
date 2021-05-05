package pl.polsl.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import pl.polsl.Model.EmptyFileException;
import pl.polsl.Model.Model;

/**
 * Servlet which handle loading data to the model and sending result to the
 * client.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
@WebServlet(name = "LoadData", urlPatterns = {"/LoadData"})
public class LoadDataServlet extends HttpServlet {

    /**
     * Model which stores data for sort visualization and implements sort
     * algorithms.
     */
    private Model model;

    private void setModelsData() throws IOException, EmptyFileException {
        loadModelsData();
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
     * Load data from file to Model.
     *
     * @throws IOException if there is no file.
     * @throws EmptyFileException if file has invalid data.
     */
    private void loadModelsData() throws IOException, EmptyFileException {
        this.model.loadData();
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
     * Handles the HTTP <code>GET</code> method which loads data to the model
     * and as a response to the client sends loaded data or error description in
     * HTML.
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
                + "         <style> "
                + "             table, th{ border: 2px solid black; padding: 5px;}"
                + "        </style>"
                + "    </head>\n"
                + "    <body style=\"text-align:center; padding: 10% 0;\">\n"
                + "        <div style=\" overflow: auto; height:auto; border: 3px solid black; margin: auto; width: 50%;background-color: #a6faff;\"> ";

        response.setContentType("text/html; charset=UTF-8");
        PrintWriter out = response.getWriter();

        if (model == null) {
            htmlCode += "Choose file before loading the data!";
        } else {
            try {
                setModelsData();
                htmlCode += prepareDataForHTML(getModelsData());
            } catch (IOException e) {
                htmlCode += e.getMessage();
            } catch (EmptyFileException e) {
                htmlCode += e.getMessage();
            } finally {
                Cookie isSortedCookie = new Cookie("isSorted", "false");
                response.addCookie(isSortedCookie); //after loading data showing sort results is restricted before sorting it
            }

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

    /**
     * Method which convert data to HTML code.
     *
     * @param data to be printed as a response.
     * @return String with HTML code.
     */
    private String prepareDataForHTML(List<Double> data) {
        String dataInHTML = "<table style:\" width: auto; overflow: auto; border-spacing: 5px; \"> <caption>Data loaded</caption>";
        dataInHTML += "<tr>";
        dataInHTML = data.stream().map(element -> "<th>" + element.toString() + "</th>").reduce(dataInHTML, String::concat);
        dataInHTML += "</tr>";
        dataInHTML += "</table>";
        return dataInHTML;
    }

}
