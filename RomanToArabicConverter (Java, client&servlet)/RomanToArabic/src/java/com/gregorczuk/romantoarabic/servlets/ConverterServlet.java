package com.gregorczuk.romantoarabic.servlets;

import com.gregorczuk.romantoarabic.server.model.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import java.io.*;
import java.util.*;

/**
 * Servlet converting given roman numerals to arabic numerals.
 * @author Patryk Gregorczuk
 * @version 5.0
 */
public class ConverterServlet extends HttpServlet 
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
    private void processRequest(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException 
    {
        resp.setContentType("text/html; charset=ISO-8859-2");
        PrintWriter out = resp.getWriter();
        HttpSession session = req.getSession(true);
        
        // Get parameter values - romanNumerals
        String romanNumerals = req.getParameter("romanNumerals");

        if(romanNumerals.length() == 0)
        {
            out.println("No data to convert!");
            return;
        }
        
        if((Converter)session.getAttribute("converter") == null)
        {
            Converter tmp = new Converter();
            session.setAttribute("converter", tmp);
        }
        Converter converter = (Converter)session.getAttribute("converter");
        
        //Splitting read line to words and puting them to temporary array.
        String[] inputRomanNumerals = romanNumerals.split(" ");
        
        Timestamp currentTimestamp = null;
        String clientAddress = null;
        try
        {
            converter.receiveData(Arrays.asList(inputRomanNumerals));
            converter.convert();
            currentTimestamp = new Timestamp(Calendar
                            .getInstance()
                            .getTime()
                            .getTime());
            clientAddress = req.getRemoteAddr();
        }
        catch(IncorrectDataException e)
        {
            out.println("Passed numerals were not correct!<br /><br />");
        }

        out.println("Conversion finished!<br /><br />");
        
        Cookie[] cookies = req.getCookies();
        int cookiesCounter = 0;
        
        if(cookies != null)
        {
            for(Cookie cookie : cookies)
            {
                if(cookie.getName().startsWith("singleConvertedNumeral"))
                    cookiesCounter++;
            }
        }
                  
        Iterator<Integer> it = converter.getResult().iterator();
        Iterator<String> it2 = converter.getRomanNumerals().iterator();

        if(it.hasNext())
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
                
                //Traversing lists with iterators, sending results to DB and saving them in cookies
                while(it.hasNext())
                {   
                    Integer arabicNumeral = it.next();
                    String romanNumeral = it2.next();

                    // Preparing query
                    String coolQuery = String.format("INSERT INTO RESULTS"
                            + "(ARABICNUMERAL, ROMANNUMERAL, DATE, ADDRESS) "
                            + "VALUES (%d, '%s', '%s', '%s')", 
                            arabicNumeral, 
                            romanNumeral, 
                            currentTimestamp, 
                            clientAddress);
                    
                    // Sending query to database
                    statement.executeUpdate(coolQuery);

                    // Print result on user screen
                    String singleConvertedNumeral = (romanNumeral + " = " + arabicNumeral + "<br />");
                    out.println(singleConvertedNumeral);

                    // Saving results in cookies
                    cookiesCounter++;
                    Cookie cookie = new Cookie("singleConvertedNumeral" + cookiesCounter, singleConvertedNumeral);
                    resp.addCookie(cookie);                
                }               
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
        // Clearing model
        converter.clearData();       
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
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException 
    {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException 
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
}
