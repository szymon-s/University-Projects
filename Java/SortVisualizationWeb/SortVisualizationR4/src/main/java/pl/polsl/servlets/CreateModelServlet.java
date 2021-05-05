package pl.polsl.servlets;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import pl.polsl.Model.Model;

/**
 * Servlet which handle creating new model and setting it as a session attribute
 * and setting cookie used as a flag determinating whether data was sorted or
 * not.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
@WebServlet(name = "CreateModel", urlPatterns = {"/CreateModel"})
public class CreateModelServlet extends HttpServlet {

    /**
     * Model which stores data.
     */
    private Model model;

    /**
     * Handles the HTTP <code>GET</code> method, it sets new model as a session
     * atribute and sets isSorted flag cookie.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        model = new Model();
        request.getSession().setAttribute("model", model);
        Cookie isSortedCookie = new Cookie("isSorted", "false");
        response.addCookie(isSortedCookie);
    }

    /**
     * Handles the HTTP <code>POST</code> method, it sets new model as a session
     * atribute and sets isSorted flag cookie.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        model = new Model();
        request.getSession().setAttribute("model", model);
        Cookie cookie = new Cookie("isSorted", "false");
        response.addCookie(cookie);
    }

}
