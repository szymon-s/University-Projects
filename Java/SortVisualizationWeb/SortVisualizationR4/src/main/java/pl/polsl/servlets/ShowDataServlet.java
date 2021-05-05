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
import pl.polsl.Model.Model;

/**
 * Servlet which handle sending sort visualization to the client.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
@WebServlet(name = "ShowData", urlPatterns = {"/ShowData"})
public class ShowDataServlet extends HttpServlet {

    /**
     * Model which stores data for sort visualization and implements sort
     * algorithms.
     */
    private Model model;

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
     * Handles the HTTP <code>GET</code> method which as a response to the
     * client sends HTML code presenting sort visualization or error
     * description.
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
                + "        <style> "
                + "              th, td { border: 2px solid black; padding: 5px;}"
                + "        </style>"
                + "    </head>\n"
                + "    <body style=\"text-align:center; padding: 10% 0;\">\n"
                + "        <div style=\" overflow: auto; height:auto; max-height: 700px; border: 3px solid black; margin: auto; width:50%; white-space: nowrap; background-color: #a6faff;\"> ";
        response.setContentType("text/html; charset=UTF-8");
        PrintWriter out = response.getWriter();
        Cookie cookies[] = request.getCookies();
        Cookie isSortedCookie = null;
        for (Cookie element : cookies) {
            if (element.getName().equals("isSorted")) {
                isSortedCookie = element;
            }
        }
        if (isSortedCookie == null) {
            htmlCode += "Load file and sort loaded data before getting result!";
        } else if (model != null && getModelsData() != null && isSortedCookie.getValue().equals("true")) {
            htmlCode += prepareDataForHTML(getModelsData(), getSortedData());
        } else {
            htmlCode += "Load file and sort loaded data before getting result!";
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
     * Method which convert data from Lists to HTML code.
     *
     * @param data original data to be printed.
     * @param dataSorted sorting steps to be printed.
     * @return String with HTML code presenting sort visualization.
     */
    private String prepareDataForHTML(List<Double> data, List<List<Double>> dataSorted) {
        String dataSortedInHTML = "<table style:\" width: auto; margin: auto; border-spacing: 5px; border: 2px solid black; \"> <caption>Sort visualization</caption>";

        dataSortedInHTML += "<tr>";
        dataSortedInHTML = data.stream().map(element -> "<th>" + element.toString() + "</th>").reduce(dataSortedInHTML, String::concat);
        dataSortedInHTML += "</tr>";
        for (List<Double> arrayList : dataSorted) {

            dataSortedInHTML += "<tr>";
            dataSortedInHTML = arrayList.stream().map(element -> "<td>" + element.toString() + "</td>").reduce(dataSortedInHTML, String::concat);
            dataSortedInHTML += "</tr>";
        }
        dataSortedInHTML += "</table>";
        return dataSortedInHTML;
    }

}
