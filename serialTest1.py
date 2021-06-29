import sys
import requests
import serial
from time import sleep
from flask import Flask, json, Response, send_from_directory, render_template, redirect, url_for, request, jsonify
from flask_cors import CORS

api = Flask(__name__, static_url_path='')
api.config['SECRET_KEY'] = 'LAIUtesting'    #JF

cors = CORS(api, resources={r"/*": {"origins": "*"}})

# Pyserial!!!
ser = serial.Serial('COM5', 9600) # Establish the connection on a specific port

@api.route('/LAIU/testSerial/<unitCommand>', methods = ['GET','POST'])
def testSerial(unitCommand):
  strCommand = unitCommand  
  params = request.form['params']

  """ The following works... try to replicate
  counter = 32 # Below 32 everything in ASCII is gibberish
  while True:
     counter +=1
     ser.write(str(chr(counter)).encode()) # Convert the decimal number to ASCII then send it to the Arduino
     print ( ser.readline() ) # Read the newest output from the Arduino
     sleep(.1) # Delay for one tenth of a second
     if counter == 255:
       return 'working'
       #counter = 32
  """
  print ( 'params ', params)
  #ser.write(b'R0')
  strCommand = strCommand + ' ' + params
  ser.write(strCommand.encode())
  retVal = ser.readline() # Read the newest output from the Arduino
  print ( retVal )
  return ( retVal ) # Read the newest output from the Arduino

  

if __name__ == '__main__':
    api.run(host="0.0.0.0", port=8686, debug=False)
