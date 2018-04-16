/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gregorczuk.romantoarabic.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet presenting history of conversions. It uses reads user cookies and
 * sends query to database to see full conversion history of all users with
 * time-when and address-who.
 * @author Patryk Gregorczuk
 * @version 5.0
 */
public class ResultsServlet extends HttpServlet 
{
    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param req servlet request
     * @param resp servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        resp.setContentType("text/html; charset=ISO-8859-2");
        PrintWriter out = resp.getWriter();
        HttpSession session = req.getSession(true);
        
        out.println("Results history from cookies: <br /><br />");
        boolean cookieFound = false;
        Cookie[] cookies = req.getCookies();
        String singleConvertedNumeral = "Results history is empty! <br /><br />";
        if(cookies != null)
        {
            for (Cookie cookie : cookies) 
            {
                if (cookie.getName().startsWith("singleConvertedNumeral")) 
                {
                    cookieFound = true;
                    singleConvertedNumeral = cookie.getValue();
                    out.println(singleConvertedNumeral);
                }
            }
        }
        if(cookieFound == false)
            out.println(singleConvertedNumeral);
        
        out.println("<hr>");
        out.println("Results history from DB: <br /><br />");
                                  
        getResultsFromDB(out, session);      
        
        out.println("</body>");
        out.println("</html>");
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() 
    {
        return "Short description";
    }// </editor-fold>
    
    /**
     * Realises SELECT * query to DB and presents results returned from DB.
     * @param out stream to send results
     * @param session current session handler
     */
    private void getResultsFromDB(PrintWriter out, HttpSession session)
    {
        Connection con = (Connection)session.getAttribute("connection");
        
        if (con == null)
        {
            // Reading parameters from web.xml file
            String dbURL = getServletContext().getInitParameter("dbURL");
            String dbUser = getServletContext().getInitParameter("dbUser");
            String dbPassword = getServletContext().getInitParameter("dbPassword");
            
            try
            {
                // Ładujemy plik z klasą sterownika bazy danych
                Class.forName("org.apache.derby.jdbc.ClientDriver");
                // Tworzymy połączenie do bazy danych
                con = DriverManager.getConnection(dbURL, dbUser, dbPassword);
                session.setAttribute("connection", con);                  
            }       
            catch (SQLException sqle) 
            {
                System.err.println("SQL exception: " + sqle.getMessage());
            } 
            catch (ClassNotFoundException cnfe) 
            {
                System.err.println("ClassNotFound exception: " + cnfe.getMessage());
            } 
        }
        
        try 
        {
            Statement statement = con.createStatement();
            
            // Wysyłamy zapytanie do bazy danych
            ResultSet rs = statement.executeQuery("SELECT * FROM RESULTS");

            // Prepare table structure
            out.println("<table>\n" +
                        "<tr>\n" +
                        "<th>ID</th>\n" +
                        "<th>Roman Numeral</th>\n" +
                        "<th>Arabic Numeral</th>\n" +
                        "<th>Date</th>\n" +
                        "<th>Address</th>\n" +
                        "</tr>\n");

            // Przeglądamy otrzymane wyniki
            while (rs.next()) 
            {
                out.println("<tr>");
                out.printf("<td>%-10s</td>", rs.getInt("ID"));
                out.printf("<td>%-20s</td>", rs.getString("ROMANNUMERAL"));
                out.printf("<td>%-9s</td>", rs.getInt("ARABICNUMERAL"));
                out.printf("<td>%-25s</td>", rs.getTimestamp("DATE"));
                out.printf("<td>%-4s</td>\n", rs.getString("ADDRESS"));
                out.println("</tr>");
            }
            out.println("</table>");
            rs.close();
        }
        catch (NullPointerException | SQLException e)
        {
            System.err.println("Could not finish operation due to: " + e.getMessage());
            
            try
            {
                if (con != null) 
                {
                    con.close();
                }
            } 
            catch (SQLException sqle) 
            {
                System.err.println("SQL exception: " + sqle.getMessage());
            }
        }
    }
}