/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.gregorczuk.romantoarabic.server.model;

/**
 * Class of exception. Can be thrown to signalise incorrect data.
 * E.g. wrong format of Rome numeral.
 * @version 2.0
 * @author Patryk Gregorczuk
 */
public class IncorrectDataException extends Exception {
    /**
     * Default constructor of this class. Does not provide additional message.
     */
    public IncorrectDataException()
    {
    }
    /**
     * Can take additional message about exception in order to display it
     * by the View.
     * @param singleInputData the message holded in exception.     
     */
    public IncorrectDataException(String singleInputData)
    {
        super(singleInputData);
    }
}
