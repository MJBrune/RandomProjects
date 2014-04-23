#region License and Comments
/*
 * Programmer: Michael J Brune <admin@mjbrune.org> Comments Designated by " "
 * 
 * Comments: I tried to comment and clean a lot of the code up with regions. 
 * Feel free to e-mail me on anything that doesn't make sense. 
 * 
 * Copywrite (C) 2012, Michael J Brune <admin@mjbrune.org>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3. All contributers must keep their code clean, commented and keep the 
 * changelog section up to date.
 * 
 * THIS SOFTWARE IS PROVIDED BY Michael J Brune ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Michael J Brune BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * ChangeLog:
 * 
 * 01/06/2012 - Felt self-conscious about my code, cleaned it up as best as possible. 
 * 01/05/2012 - Added more support for setting paths such as set backup path and worldlocation. 
 * 01/05/2012 - Added MoreTerra support. 
 * 01/04/2012 - Removed TCPVCON requirements by parsing the server output
 * this means that users can't use the playing command. 
 * 01/04/2012 - Added try/catch to each server thread. 
 * 01/04/2012 - Added a license that requires a changelog. 
 * 01/03/2012 - Added Updater. As well as SetServerExe and Save buttons. 
 * 12/30/2011 - Version 2.0.0 Released. 
 * 12/15/2011 - Version 1.0.0 Released. Inital functions working. 
*/
#endregion
using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;
using System.Net;

namespace Arra_sServerApp
{
    public partial class frmArrasServerApp : Form
    {
        #region initalization
        //Version - for updating. Set with application version. 
        //StreamWriters - for the input part of the server. 
        //ServerExe - for changable exe files. Set with default. 
        //Serverpids - for sorting out what server is being reported by tcpvcon. 
        string version = "2.0.9";
        string histlog = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\histlog.txt";
        StreamWriter StreamWriterServer1;
        StreamWriter StreamWriterServer2;
        StreamWriter StreamWriterServer3;
        StreamWriter StreamWriterServer4;
        string ServerExe = 
            "C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\TerrariaServer.exe";

        public frmArrasServerApp()
        {
            InitializeComponent();
        }

        private void frmArrasServerApp_Load(object sender, EventArgs e)
        {
            //Write Start time to History Listbox and to log file. 
            AddHistBoxItem("[" + DateTime.Now + "] ASCS Started");
            try
            {
                System.IO.File.AppendAllText(histlog, "[" + DateTime.Now + "] ASCS Started" + "\n");
            }
            catch
            { 
                MessageBox.Show(
                    "The log file path was not found, please select a directory to create a histlog.txt", 
                    "Log File Path Not Found");
                if (fbdHistlog.ShowDialog() == DialogResult.OK)
                {
                    histlog = fbdHistlog.SelectedPath;
                }
                else
                {
                    MessageBox.Show("So you cancelled out of that dialog box... That is bad... "
                        + "BAD USER! The program will now exit", 
                        "Good Bye");
                    Application.Exit();
                }
                System.IO.File.AppendAllText(histlog, "[" + DateTime.Now + "] ASCS Started" + "\n");
            }
            //Make sure "say" is selected in the Command type. 
            cboCMDType.SelectedIndex = 0;
            //Make sure the server combo box is sorted. 
            cboServerNumb.Sorted = true;
            //add a new event handler to the listbox history so you can easily ban ips. 
            lstHistory.MouseDoubleClick += new MouseEventHandler(lstHistory_MouseDoubleClick);
            //add a new event handler to the listbox connections so you can easily ban ips. 
            lstConnections.MouseDoubleClick += new MouseEventHandler(lstConnections_MouseDoubleClick);
            //Fill out version label with current version then call the update checker function. 
            lblVersion.Text = "Version: " + version;
            checkforupdates();
        }
        #endregion

        #region updating
        private void btnUpdates_Click(object sender, EventArgs e)
        {
            checkforupdates();
        }

        private void checkforupdates()
        {
            //If there is no connection it hangs here, update the lbl box with that information. 
            lblVersion.Text = "Version: " + version + " (No Connection...)";

            //create a new webclient and download the file. 
            WebClient VersionDownload = new WebClient();
            VersionDownload.DownloadFile("http://www.mjbrune.org/files/arra/version.txt",
                @"./version.txt");

            //Read the file into a string then delete it. 
            //The file contains a string of numbers that makes up a version. 
            //e.g. "2.0.1" 
            string versionfile = File.ReadAllText("./version.txt");
            File.Delete("./version.txt");
            //If the current app version doesn't match the file version... 
            if (versionfile != version)
            {
                //Set the label box to reflect and update is needed and... 
                lblVersion.Text = "Version: " + version + " (Update Needed)";
                //Prompt the user to go to the site to download the new version. 
                DialogResult VersionDownloadCheck = MessageBox.Show("\t\t   An update is available " + 
                    Environment.NewLine + "\t Please go to http://www.mjbrune.org/files/arra/ " +
                    Environment.NewLine + "\t\t         Go to the site?", 
                    "A NEW VERSION IS AVAILABLE", MessageBoxButtons.YesNo);
                if (VersionDownloadCheck == DialogResult.Yes)
                {
                    //If they say yes then open the browser for them. 
                    System.Diagnostics.Process.Start("http://www.mjbrune.org/files/arra/");
                }
            }
            else
            {
                //If the app is up to date then just reflect that in the label. 
                lblVersion.Text = "Version: " + version + " (Up To Date)";
            }
        }
        #endregion

        #region Backup & Restore
        private void btnbackup_Click(object sender, EventArgs e)
        {
            //backup runs this cmd command which copies the entire world directory to their desktop 
            //this uses a hardcoded path and needs to be replaced. 
            //The replacement should have no calls to cmd and no hardcoded paths. 
            string args = "/c XCOPY \"%USERPROFILE%\\Documents\\My Games\\Terraria\\Worlds\" "
                +"\"%USERPROFILE%\\Desktop\\Backups\\%date:/=-%\\%time:~0,2%-%time:~3,2%\" /i";
            if (fbdBackupLocation.SelectedPath != "" && fbdWorldLocation.SelectedPath != "")
            {
                args = "/c XCOPY \"" + fbdWorldLocation.SelectedPath 
                    + "\" \"" + fbdBackupLocation.SelectedPath 
                    + "\\%date:/=-%\\%time:~0,2%-%time:~3,2%\" /i";
            }
            else if (fbdWorldLocation.SelectedPath != "")
            {
                args = "/c XCOPY \"" 
                    + fbdWorldLocation.SelectedPath 
                    + "\"%USERPROFILE%\\Desktop\\Backups\\%date:/=-%\\%time:~0,2%-%time:~3,2%\" /i";
            }
            else if (fbdBackupLocation.SelectedPath != "")
            {
                args = "/c XCOPY \"%USERPROFILE%\\Documents\\My Games\\Terraria\\Worlds\" \"" 
                    + fbdBackupLocation.SelectedPath 
                    + "\\%date:/=-%\\%time:~0,2%-%time:~3,2%\" /i";
            }
            System.Diagnostics.Process.Start("cmd.exe", args);

            //Report that the backup has been made to the history listbox, 
            //report it and scroll to the bottom of the history listbox. 
            AddHistBoxItem("[" + DateTime.Now + "] Backup Made");
            System.IO.File.AppendAllText(histlog, "[" + DateTime.Now + "] Backup Made" + "\n");
            lstscrolldown();
        }

        private void btnRestore_Click(object sender, EventArgs e)
        {
            //Show the Restore Dialog box... 
            //If the user didn't hit cancel... 
            if (ofdRestore.ShowDialog() == DialogResult.OK)
            {
                //create a variable to loop with. 
                int loop = 0;
                //for each string in the filenames (because you can restore more than one world at once) 
                foreach (String file in ofdRestore.FileNames)
                {
                    //I put all the safefilenames into this array... 
                    //I do this because I need the actual filename without the path. 
                    string[] filename = ofdRestore.SafeFileNames;
                    //and copy the files over one by one using loop 
                    //to specify which filename in the array.
                    //dest must be set in a string because of the environment call to my documents. 
                    string dest = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                        + "\\My Games\\Terraria\\Worlds\\" + filename[loop];
                    if (fbdWorldLocation.SelectedPath != "")
                    {
                        dest = fbdWorldLocation.SelectedPath + "\\" + filename[loop];
                    }
                    System.IO.File.Copy(file, dest, true);

                    //Add it to the history box, scroll history box down, 
                    //log and add one to loop for the next filename. 
                    AddHistBoxItem("[" + DateTime.Now + "] Restore of " + filename[loop] + " Made");
                    System.IO.File.AppendAllText(histlog, "[" + DateTime.Now + "] Restore of " 
                        + filename[loop] + " Made" + "\n");
                    lstscrolldown();
                    loop++;
                }
            }

        }
        #endregion

        #region lstscrolling
        //these two functions scroll lsthist and lstserver down when they get populated. 
        void lstscrolldown()
        {
            int NumberOfItems = lstHistory.ClientSize.Height / lstHistory.ItemHeight;
            lstHistory.TopIndex = lstHistory.Items.Count - NumberOfItems + 1;
        }

        void lstserverdown()
        {
            int NumberOfItems = lstServer.ClientSize.Height / lstServer.ItemHeight;
            lstServer.TopIndex = lstServer.Items.Count - NumberOfItems + 1;
        }
        #endregion

        #region Server Start Button click
        //All these do is add the server to the cbo box, 
        //enable/disable buttons when started and start the serverthreads. 
        public void btnServer_Click(object sender, EventArgs e)
        {
            btnSave1.Enabled = true;
            btnServer1Stop.Enabled = true;
            btnServerStart.Enabled = false;
            btnExitServer1.Enabled = true;
            AddCboBoxItem("Server 1");
            Thread thread = new Thread(new ThreadStart(server1));
            thread.Start();
        }
        private void btnServer2Start_Click(object sender, EventArgs e)
        {
            btnSave2.Enabled = true;
            btnServer2Stop.Enabled = true;
            btnServer2Start.Enabled = false;
            btnExitServer2.Enabled = true;
            AddCboBoxItem("Server 2");
            Thread thread = new Thread(new ThreadStart(server2));
            thread.Start();
        }
        private void btnServer3Start_Click(object sender, EventArgs e)
        {
            btnSave3.Enabled = true;
            btnServer3Stop.Enabled = true;
            btnServer3Start.Enabled = false;
            btnExitServer3.Enabled = true;
            AddCboBoxItem("Server 3");
            Thread thread = new Thread(new ThreadStart(server3));
            thread.Start();
        }

        private void btnServer4Start_Click(object sender, EventArgs e)
        {
            btnSave4.Enabled = true;
            btnServer4Stop.Enabled = true;
            btnServer4Start.Enabled = false;
            btnExitServer4.Enabled = true;
            AddCboBoxItem("Server 4");
            Thread thread = new Thread(new ThreadStart(server4));
            thread.Start();
        }
        #endregion

        #region ServerThreads
        public void server1()
        {
            Process myProcess = new Process();
            //set default arguments here. 
            string args = "-port " + nudPort1.Value.ToString() + " -players " 
                + nudPlayers1.Value.ToString() + " -world \"" 
                + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                + "\\My Games\\Terraria\\Worlds\\world1.wld\" -banlist "
                + "\"C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\banlist.txt\"";
            //use config instead if the config button is checked. 
            if (cbkConfig1.Checked)
            {
                args = ("-config " + "\"" + ofdConfig1.FileName + "\"");
            }
            //if the config button isn't checked and the world filename has been set, use it. 
            else if (ofdWorld1.FileName != "")
            {
                args = "-port " + nudPort1.Value.ToString() 
                    + " -players " + nudPlayers1.Value.ToString() 
                    + " -world \"" + ofdWorld1.FileName 
                    + "\" -banlist \"C:\\Program Files (x86)\\Steam"
                    + "\\steamapps\\common\\terraria\\banlist.txt\"";
            }
            //if the executable path has been set use that instead of the default. 
            if (ofdServerExe.FileName != "")
                ServerExe = ofdServerExe.FileName;
            //Try to start the thread for the server. 
            try
            {
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ServerExe, args);
                myProcessStartInfo.UseShellExecute = false;
                myProcessStartInfo.CreateNoWindow = true;
                myProcessStartInfo.RedirectStandardOutput = true;
                myProcessStartInfo.RedirectStandardInput = true;
                myProcess.StartInfo = myProcessStartInfo;
                myProcess.Start();
                StreamWriterServer1 = myProcess.StandardInput;
                myProcess.OutputDataReceived += new DataReceivedEventHandler(OutputHandlerServer1);
                myProcess.BeginOutputReadLine();
            }
            // if it fails error out and reset all the buttons back. 
            catch
            {
                string error = "Terraria Server Failed to launch\nPlease Check Your settings.";
                MessageBox.Show(error, "Error");
                Restart1();

            }
        }

        public void server2()
        {
            try
            {
                Process myProcess = new Process();
                string args = "-port " + nudPort2.Value.ToString() 
                    + " -players " + nudPlayers2.Value.ToString() 
                    + " -world \"" + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                    + "\\My Games\\Terraria\\Worlds\\world2.wld\" -banlist "
                    + "\"C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\banlist.txt\"";
                if (cbkConfig2.Checked)
                {
                    args = ("-config " + "\"" + ofdConfig2.FileName + "\"");
                }
                else if (ofdWorld2.FileName != "")
                {
                    args = "-port " + nudPort2.Value.ToString() 
                        + " -players " 
                        + nudPlayers2.Value.ToString() 
                        + " -world \"" + ofdWorld2.FileName 
                        + "\" -banlist "
                        + "\"C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\banlist.txt\"";
                }
                if (ofdServerExe.FileName != "")
                    ServerExe = ofdServerExe.FileName;
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ServerExe, args);
                myProcessStartInfo.UseShellExecute = false;
                myProcessStartInfo.CreateNoWindow = true;
                myProcessStartInfo.RedirectStandardOutput = true;
                myProcessStartInfo.RedirectStandardInput = true;
                myProcess.StartInfo = myProcessStartInfo;
                myProcess.Start();
                StreamWriterServer2 = myProcess.StandardInput;
                myProcess.OutputDataReceived += new DataReceivedEventHandler(OutputHandlerServer2);
                myProcess.BeginOutputReadLine();
            }
            catch
            {
                string error = "Terraria Server Failed to launch\nPlease Check Your settings.";
                MessageBox.Show(error, "Error");
                Restart2();

            }
        }

        public void server3()
        {
            try
            {
                Process myProcess = new Process();
                string args = "-port " + nudPort3.Value.ToString() 
                    + " -players " + nudPlayers3.Value.ToString() 
                    + " -world \"" + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                    + "\\My Games\\Terraria\\Worlds\\world3.wld\" -banlist "
                    + "\"C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\banlist.txt\"";
                if (cbkConfig2.Checked)
                {
                    args = ("-config " + "\"" + ofdConfig3.FileName + "\"");
                }
                else if (ofdWorld3.FileName != "")
                {
                    args = "-port " + nudPort3.Value.ToString() + " -players " 
                        + nudPlayers3.Value.ToString() + " -world \"" + ofdWorld3.FileName 
                        + "\" -banlist \"C:\\Program Files (x86)\\Steam"
                        + "\\steamapps\\common\\terraria\\banlist.txt\"";
                }
                if (ofdServerExe.FileName != "")
                    ServerExe = ofdServerExe.FileName;
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ServerExe, args);
                myProcessStartInfo.UseShellExecute = false;
                myProcessStartInfo.CreateNoWindow = true;
                myProcessStartInfo.RedirectStandardOutput = true;
                myProcessStartInfo.RedirectStandardInput = true;
                myProcess.StartInfo = myProcessStartInfo;
                myProcess.Start();
                StreamWriterServer3 = myProcess.StandardInput;
                myProcess.OutputDataReceived += new DataReceivedEventHandler(OutputHandlerServer3);
                myProcess.BeginOutputReadLine();
            }
            catch
            {
                string error = "Terraria Server Failed to launch\nPlease Check Your settings.";
                MessageBox.Show(error, "Error");
                Restart3();

            }
        }

        public void server4()
        {
            try
            {
                Process myProcess = new Process();
                string args = "-port " + nudPort4.Value.ToString() + " -players " 
                    + nudPlayers4.Value.ToString() + " -world \"" 
                    + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                    + "\\My Games\\Terraria\\Worlds\\world2.wld\" -banlist "
                    + "\"C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\banlist.txt\"";
                if (cbkConfig4.Checked)
                {
                    args = ("-config " + "\"" + ofdConfig4.FileName + "\"");
                }
                else if (ofdWorld4.FileName != "")
                {
                    args = "-port " + nudPort4.Value.ToString() + " -players " 
                        + nudPlayers4.Value.ToString() + " -world \"" + ofdWorld4.FileName
                        + "\" -banlist \"C:\\Program Files (x86)\\Steam"
                        + "\\steamapps\\common\\terraria\\banlist.txt\"";
                }
                if (ofdServerExe.FileName != "")
                    ServerExe = ofdServerExe.FileName;
                ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ServerExe, args);
                myProcessStartInfo.UseShellExecute = false;
                myProcessStartInfo.CreateNoWindow = true;
                myProcessStartInfo.RedirectStandardOutput = true;
                myProcessStartInfo.RedirectStandardInput = true;
                myProcess.StartInfo = myProcessStartInfo;
                myProcess.Start();
                StreamWriterServer4 = myProcess.StandardInput;
                myProcess.OutputDataReceived += new DataReceivedEventHandler(OutputHandlerServer4);
                myProcess.BeginOutputReadLine();
            }
            catch
            {
                string error = "Terraria Server Failed to launch\nPlease Check Your settings.";
                MessageBox.Show(error, "Error");
                Restart2();

            }
        }
        #endregion

        #region Thread Delegation
        private delegate void AddHistBoxItemDelegate(object item);
        private delegate void AddListBoxItemDelegate(object item);
        private delegate void AddConnBoxItemDelegate(object item);
        private delegate void AddCboBoxItemDelegate(object item);
        private delegate void Restart1Delegate();
        private delegate void Restart2Delegate();
        private delegate void Restart3Delegate();

        private void AddCboBoxItem(object item)
        {
            if (this.cboServerNumb.InvokeRequired)
            {
                // This is a worker thread so delegate the task.
                this.cboServerNumb.Invoke(new AddCboBoxItemDelegate(this.AddCboBoxItem), item);
            }
            else
            {
                // This is the UI thread so perform the task.
                this.cboServerNumb.Items.Add(item);
                cboServerNumb.SelectedIndex = 0;
            }
        }

        private void AddListBoxItem(object item)
        {
            if (this.lstServer.InvokeRequired)
            {
                this.lstServer.Invoke(new AddListBoxItemDelegate(this.AddListBoxItem), item);
            }
            else
            {
                this.lstServer.Items.Add(item);
                lstserverdown();
            }
        }

        private void AddConnBoxItem(object item)
        {

            if (this.lstConnections.InvokeRequired)
            {
                this.lstConnections.Invoke(new AddCboBoxItemDelegate(this.AddConnBoxItem), item);
            }
            else
            {
                this.lstConnections.Items.Add(item);
            }
        }

        private void AddHistBoxItem(object item)
        {
            if (this.lstHistory.InvokeRequired)
            {
                this.lstHistory.Invoke(new AddHistBoxItemDelegate(this.AddHistBoxItem), item);
            }
            else
            {
                this.lstHistory.Items.Add(item);
                lstscrolldown();
            }
        }

        private void Restart1()
        {
            if (this.btnSave1.InvokeRequired)
            {
                this.btnSave1.Invoke(new Restart1Delegate(this.Restart1));
            }
            else
            {
                this.btnSave1.Enabled = false;
            }
            if (this.btnServer1Stop.InvokeRequired)
            {
                this.btnServer1Stop.Invoke(new Restart1Delegate(this.Restart1));
            }
            else
            {
                this.btnServer1Stop.Enabled = false;
            }
            if (this.btnServerStart.InvokeRequired)
            {
                this.btnServerStart.Invoke(new Restart1Delegate(this.Restart1));
            }
            else
            {
                this.btnServerStart.Enabled = true;
            }
            if (this.btnExitServer1.InvokeRequired)
            {
                this.btnExitServer1.Invoke(new Restart1Delegate(this.Restart1));
            }
            else
            {
                this.btnExitServer1.Enabled = false;
            }
        }

        private void Restart2()
        {
            if (this.btnSave2.InvokeRequired)
            {
                this.btnSave2.Invoke(new Restart2Delegate(this.Restart2));
            }
            else
            {
                this.btnSave2.Enabled = false;
            }
            if (this.btnServer2Stop.InvokeRequired)
            {
                this.btnServer2Stop.Invoke(new Restart2Delegate(this.Restart2));
            }
            else
            {
                this.btnServer2Stop.Enabled = false;
            }
            if (this.btnServer2Start.InvokeRequired)
            {
                this.btnServer2Start.Invoke(new Restart2Delegate(this.Restart2));
            }
            else
            {
                this.btnServer2Start.Enabled = true;
            }
            if (this.btnExitServer2.InvokeRequired)
            {
                this.btnExitServer2.Invoke(new Restart2Delegate(this.Restart2));
            }
            else
            {
                this.btnExitServer2.Enabled = false;
            }
        }

        private void Restart3()
        {
            if (this.btnSave3.InvokeRequired)
            {
                this.btnSave3.Invoke(new Restart3Delegate(this.Restart3));
            }
            else
            {
                this.btnSave3.Enabled = false;
            }
            if (this.btnServer3Stop.InvokeRequired)
            {
                this.btnServer3Stop.Invoke(new Restart3Delegate(this.Restart3));
            }
            else
            {
                this.btnServer3Stop.Enabled = false;
            }
            if (this.btnServer3Start.InvokeRequired)
            {
                this.btnServer3Start.Invoke(new Restart3Delegate(this.Restart3));
            }
            else
            {
                this.btnServer3Start.Enabled = true;
            }
            if (this.btnExitServer3.InvokeRequired)
            {
                this.btnExitServer3.Invoke(new Restart3Delegate(this.Restart3));
            }
            else
            {
                this.btnExitServer3.Enabled = false;
            }
        }

        private void Restart4()
        {
            if (this.btnSave4.InvokeRequired)
            {
                this.btnSave4.Invoke(new Restart3Delegate(this.Restart4));
            }
            else
            {
                this.btnSave4.Enabled = false;
            }
            if (this.btnServer4Stop.InvokeRequired)
            {
                this.btnServer4Stop.Invoke(new Restart3Delegate(this.Restart4));
            }
            else
            {
                this.btnServer4Stop.Enabled = false;
            }
            if (this.btnServer4Start.InvokeRequired)
            {
                this.btnServer4Start.Invoke(new Restart3Delegate(this.Restart4));
            }
            else
            {
                this.btnServer4Start.Enabled = true;
            }
            if (this.btnExitServer4.InvokeRequired)
            {
                this.btnExitServer4.Invoke(new Restart3Delegate(this.Restart4));
            }
            else
            {
                this.btnExitServer4.Enabled = false;
            }
        }

        #endregion

        #region outputhandlers
        private void OutputHandlerServer1(object sendingProcess, DataReceivedEventArgs outLine)
        {
            if (!String.IsNullOrEmpty(outLine.Data))
            {
                //add the terraria server output to the server listbox. 
                AddListBoxItem("[Server 1]" + "[" + DateTime.Now + "] " + outLine.Data);
                //split out the has joined, is connecting and has left to the lsthistbox. 
                if (outLine.Data.Contains("has joined") || 
                    outLine.Data.Contains("is connecting") || 
                    outLine.Data.Contains("has left") || 
                    outLine.Data.Contains("was booted"))
                {
                    AddHistBoxItem("[Server 1]" + "[" + DateTime.Now + "] " + outLine.Data);
                    System.IO.File.AppendAllText(histlog, "[Server 1]" + "[" + DateTime.Now + "] " 
                        + outLine.Data + "\n");
                }
                else
                {
                    //split out the terraria server output line to parse it for an ip and username. 
                    string text = outLine.Data.ToString();
                    char[] ipDelimiterChars = { '(', ')', ':' };
                    char[] nameDelimiterChars = { ']', '(' };
                    string[] ipattempt = text.Split(ipDelimiterChars);
                    string[] name = text.Split(nameDelimiterChars);

                    //try to get an ip. the first try/catch is so 
                    //if the line doesn't contain an ip it doesn't worry about it.
                    //The second try/catch is because of the extra : issue as mentioned 
                    //in the doubleclick listconn/hist region. 
                    try
                    {
                        try
                        {
                            string sip = ipattempt[1];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 1: " + name[0] + "|" + ip.ToString() + "|");
                        }
                        catch
                        {
                            string sip = ipattempt[2];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 1" + name[0] + "|" + ip.ToString() + "|");
                        }
                    }
                    catch { };
                }
            }
        }

        private void OutputHandlerServer2(object sendingProcess, DataReceivedEventArgs outLine)
        {
            if (!String.IsNullOrEmpty(outLine.Data))
            {
                AddListBoxItem("[Server 2]" + "[" + DateTime.Now + "] " + outLine.Data);
                if (outLine.Data.Contains("has joined") || 
                    outLine.Data.Contains("is connecting") || 
                    outLine.Data.Contains("has left") || 
                    outLine.Data.Contains("was booted"))
                {
                    AddHistBoxItem("[Server 2]" + "[" + DateTime.Now + "] " + outLine.Data);
                    System.IO.File.AppendAllText(histlog, "[Server 2]" + "[" + DateTime.Now + "] " 
                        + outLine.Data + "\n");
                }
                else
                {
                    string text = outLine.Data.ToString();
                    char[] ipDelimiterChars = { '(', ')', ':' };
                    char[] nameDelimiterChars = { ']', '(' };
                    string[] ipattempt = text.Split(ipDelimiterChars);
                    string[] name = text.Split(nameDelimiterChars);
                    try
                    {
                        try
                        {
                            string sip = ipattempt[1];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 2: " + name[0] + "|" + ip.ToString() + "|");
                        }
                        catch
                        {
                            string sip = ipattempt[2];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 2" + name[0] + "|" + ip.ToString() + "|");
                        }
                    }
                    catch { };
                }
            }
        }

        private void OutputHandlerServer3(object sendingProcess, DataReceivedEventArgs outLine)
        {
            if (!String.IsNullOrEmpty(outLine.Data))
            {
                AddListBoxItem("[Server 3]" + "[" + DateTime.Now + "] " + outLine.Data);
                if (outLine.Data.Contains("has joined") || 
                    outLine.Data.Contains("is connecting") || 
                    outLine.Data.Contains("has left") || 
                    outLine.Data.Contains("was booted"))
                {
                    AddHistBoxItem("[Server 3]" + "[" + DateTime.Now + "] " + outLine.Data);
                    System.IO.File.AppendAllText(histlog, "[Server 3]" + "[" + DateTime.Now + "] " 
                        + outLine.Data + "\n");
                }
                else
                {
                    string text = outLine.Data.ToString();
                    char[] ipDelimiterChars = { '(', ')', ':' };
                    char[] nameDelimiterChars = { ']', '(' };
                    string[] ipattempt = text.Split(ipDelimiterChars);
                    string[] name = text.Split(nameDelimiterChars);
                    try
                    {
                        try
                        {
                            string sip = ipattempt[1];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 3: " + name[0] + "|" + ip.ToString() + "|");
                        }
                        catch
                        {
                            string sip = ipattempt[2];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 3" + name[0] + "|" + ip.ToString() + "|");
                        }
                    }
                    catch { };
                }
            }
        }

        private void OutputHandlerServer4(object sendingProcess, DataReceivedEventArgs outLine)
        {
            if (!String.IsNullOrEmpty(outLine.Data))
            {
                AddListBoxItem("[Server 4]" + "[" + DateTime.Now + "] " + outLine.Data);
                if (outLine.Data.Contains("has joined") || 
                    outLine.Data.Contains("is connecting") || 
                    outLine.Data.Contains("has left") || 
                    outLine.Data.Contains("was booted"))
                {
                    AddHistBoxItem("[Server 4]" + "[" + DateTime.Now + "] "
                        + outLine.Data);
                    System.IO.File.AppendAllText(histlog, "[Server 4]" + "[" + DateTime.Now + "] " 
                        + outLine.Data + "\n");
                }
                else
                {
                    string text = outLine.Data.ToString();
                    char[] ipDelimiterChars = { '(', ')', ':' };
                    char[] nameDelimiterChars = { ']', '(' };
                    string[] ipattempt = text.Split(ipDelimiterChars);
                    string[] name = text.Split(nameDelimiterChars);
                    try
                    {
                        try
                        {
                            string sip = ipattempt[1];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 4: " + name[0] + "|" + ip.ToString() + "|");
                        }
                        catch
                        {
                            string sip = ipattempt[2];
                            IPAddress ip;
                            IPAddress.TryParse(sip, out ip);
                            AddConnBoxItem("Server 4" + name[0] + "|" + ip.ToString() + "|");
                        }
                    }
                    catch { };
                }
            }
        }
        #endregion

        #region ServerStopExit
        private void btnServer1Stop_Click(object sender, EventArgs e)
        {
            btnSave1.Enabled = false;
            btnServer1Stop.Enabled = false;
            btnServerStart.Enabled = true;
            btnExitServer1.Enabled = false;
            StreamWriterServer1.WriteLine("exit-nosave");
            cboServerNumb.Items.Remove("Server 1");
        }

        private void btnServer2Stop_Click(object sender, EventArgs e)
        {
            btnSave2.Enabled = false;
            btnServer2Stop.Enabled = false;
            btnServer2Start.Enabled = true;
            btnExitServer2.Enabled = false;
            StreamWriterServer2.WriteLine("exit-nosave");
            cboServerNumb.Items.Remove("Server 2");
        }

        private void btnServer3Stop_Click(object sender, EventArgs e)
        {
            btnSave3.Enabled = false;
            btnServer3Stop.Enabled = false;
            btnServer3Start.Enabled = true;
            btnExitServer3.Enabled = false;
            StreamWriterServer3.WriteLine("exit-nosave");
            cboServerNumb.Items.Remove("Server 3");
        }

        private void btnServer4Stop_Click(object sender, EventArgs e)
        {
            btnSave4.Enabled = false;
            btnServer4Stop.Enabled = false;
            btnServer4Start.Enabled = true;
            btnExitServer4.Enabled = false;
            StreamWriterServer4.WriteLine("exit-nosave");
            cboServerNumb.Items.Remove("Server 4");
        }

        private void btnExitServer1_Click(object sender, EventArgs e)
        {
            btnSave1.Enabled = false;
            btnServer1Stop.Enabled = false;
            btnServerStart.Enabled = true;
            btnExitServer1.Enabled = false;
            StreamWriterServer1.WriteLine("exit");
            cboServerNumb.Items.Remove("Server 1");
        }

        private void btnExitServer2_Click(object sender, EventArgs e)
        {
            btnSave2.Enabled = false;
            btnServer2Stop.Enabled = false;
            btnServer2Start.Enabled = true;
            btnExitServer2.Enabled = false;
            StreamWriterServer2.WriteLine("exit");
            cboServerNumb.Items.Remove("Server 2");
        }

        private void btnExitServer3_Click(object sender, EventArgs e)
        {
            btnSave3.Enabled = false;
            btnServer3Stop.Enabled = false;
            btnServer3Start.Enabled = true;
            btnExitServer3.Enabled = false;
            StreamWriterServer3.WriteLine("exit");
            cboServerNumb.Items.Remove("Server 3");
        }

        private void btnExitServer4_Click(object sender, EventArgs e)
        {
            btnSave4.Enabled = false;
            btnServer4Stop.Enabled = false;
            btnServer4Start.Enabled = true;
            btnExitServer4.Enabled = false;
            StreamWriterServer4.WriteLine("exit");
            cboServerNumb.Items.Remove("Server 4");
        }

        #endregion

        #region doubleclick listconn/hist
        private void lstHistory_MouseDoubleClick(object sender, EventArgs e)
        {
            //I am sure you are wondering why there is a try/catch instead of a try/catch 
            //it's simple really, TerrariaServer.exe has a fun game where it randomly will throw ":" 
            //into the stdout for some reason, 
            //I don't know why and since I use : to figure out which part 
            //of the output (127.0.0.1:7777) is the ip (127.0.0.1) and which part is the port (:7777) 
            //I have to have two try/catchs, one to see if the the line contains the ip, 
            //if not no big deal and move on. 
            //The other to see if one of the 2 fields that can contain an ip actually does. 

            //The extra ":" example. 
            //so if the line is "[Server 1][1/1/2012 10:00:30 PM] 127.0.0.1:7777 is connecting..." 
            //it will sometimes appear like this: 
            //"[Server 1][1/1/2012 10:00:30 PM]: 127.0.0.1:7777 is connecting..." 
            //so first I try to get the ip with field 8 (with the extra ":") 
            //then without it which is field 6. 
            try
            {
                string text = lstHistory.SelectedItem.ToString();
                char[] delimiterChars = { ' ', ':' };
                string[] words = text.Split(delimiterChars);
                try
                {
                    string sip = words[8];
                    IPAddress ip;
                    IPAddress.TryParse(sip, out ip);
                    txtBanIP.Text = ip.ToString();
                }
                catch
                {
                    string sip = words[6];
                    IPAddress ip;
                    IPAddress.TryParse(sip, out ip);
                    txtBanIP.Text = ip.ToString();
                }
            }
            catch
            {
                MessageBox.Show("Please select a line containing an ip address", "An error occured");
            }
        }

        private void lstConnections_MouseDoubleClick(object sender, EventArgs e)
        {
            try
            {
                string text = lstConnections.SelectedItem.ToString();
                char[] delimiterChars = { '|' };
                string[] words = text.Split(delimiterChars);
                string sip = words[1];
                IPAddress ip;
                IPAddress.TryParse(sip, out ip);
                txtBanIP.Text = ip.ToString();
            }
            catch
            {
                MessageBox.Show("Please select a line containing an ip address", "An error occured");
            }
        }
        #endregion

        #region Save
        private void btnSave1_Click(object sender, EventArgs e)
        {
            StreamWriterServer1.WriteLine("save");
        }

        private void btnSave2_Click(object sender, EventArgs e)
        {
            StreamWriterServer2.WriteLine("save");
        }

        private void btnSave3_Click(object sender, EventArgs e)
        {
            StreamWriterServer3.WriteLine("save");
        }

        private void btnSave4_Click(object sender, EventArgs e)
        {
            StreamWriterServer4.WriteLine("save");
        }
        #endregion

        #region MoreTerra
        //Simple dependency check then start the thread to create 2 proccesses. 
        private void btnMoreTerraExe_Click(object sender, EventArgs e)
        {
            if (ofdMoreTerra.ShowDialog() == DialogResult.OK)
            { 

            }
        }

        private void btnWorldPic1_Click(object sender, EventArgs e)
        {
            if (ofdMoreTerra.FileName == "")
            {
                if (ofdMoreTerra.ShowDialog() == DialogResult.OK)
                {

                }
                else
                {
                    MessageBox.Show("Please set the path to MoreTerra's exe file", "Error");
                    return;
                }
            }
            if (fbdWorldPics.SelectedPath == "")
            {
                if (fbdWorldPics.ShowDialog() == DialogResult.OK)
                {

                }
                else
                {
                    MessageBox.Show("Please set world picture save location", "Error");
                    return;
                }
            }
            Thread thread = new Thread(new ThreadStart(worldpicprocess1));
            thread.Start();
        }

        private void btnWorldPic2_Click(object sender, EventArgs e)
        {
            if (ofdMoreTerra.FileName == "")
            {
                if (ofdMoreTerra.ShowDialog() == DialogResult.OK)
                {

                }
                else
                {
                    MessageBox.Show("Please set the path to MoreTerra's exe file", "Error");
                    return;
                }
            }
            if (fbdWorldPics.SelectedPath == "")
            {
                if (fbdWorldPics.ShowDialog() == DialogResult.OK)
                {

                }
                else
                {
                    MessageBox.Show("Please set world picture save location", "Error");
                    return;
                }
            }
            Thread thread = new Thread(new ThreadStart(worldpicprocess2));
            thread.Start();
        }

        private void btnWorldPic3_Click(object sender, EventArgs e)
        {
            if (ofdMoreTerra.FileName == "")
            {
                if (ofdMoreTerra.ShowDialog() == DialogResult.OK)
                {

                }
                else
                {
                    MessageBox.Show("Please set the path to MoreTerra's exe file", "Error");
                    return;
                }
            }
            if (fbdWorldPics.SelectedPath == "")
            {
                if (fbdWorldPics.ShowDialog() == DialogResult.OK)
                {

                }
                else
                {
                    MessageBox.Show("Please set world picture save location", "Error");
                    return;
                }
            }
            Thread thread = new Thread(new ThreadStart(worldpicprocess3));
            thread.Start();
        }

        private void worldpicprocess1()
        {
            string openpicname = fbdWorldPics.SelectedPath + "\\world1.png\"";
            string args = "-w \"" + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                + "\\My Games\\Terraria\\Worlds\\world1.wld\" -o \"" 
                + fbdWorldPics.SelectedPath + "\\world1.png\"";
            if (ofdWorld1.FileName != "")
            {
                string worldname = ofdWorld1.SafeFileName;
                char[] delimiterChars = { '.' };
                string[] pngname = worldname.Split(delimiterChars);
                string picname = pngname[0];
                args = "-w \"" + ofdWorld1.FileName + "\" -o \"" 
                    + fbdWorldPics.SelectedPath + "\\" + picname + ".png\"";
            }

            Process myProcess = new Process();
            ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ofdMoreTerra.FileName, args);
            myProcessStartInfo.UseShellExecute = false;
            myProcessStartInfo.CreateNoWindow = true;
            myProcess.StartInfo = myProcessStartInfo;
            myProcess.Start();
            myProcess.WaitForExit();
            myProcess.Close();

            Process openpicture = new Process();
            if (ofdWorld1.FileName != "")
            {
                string worldname = ofdWorld1.SafeFileName;
                char[] delimiterChars = { '.' };
                string[] pngname = worldname.Split(delimiterChars);
                string picname = pngname[0];
                openpicname = fbdWorldPics.SelectedPath + "\\" + picname + ".png";
            }
            ProcessStartInfo openpictureStartInfo = new ProcessStartInfo("explorer.exe", openpicname);
            //Don't use a shell, create a window and allow redirection of stdout. 
            openpictureStartInfo.UseShellExecute = false;
            openpictureStartInfo.CreateNoWindow = true;
            openpictureStartInfo.RedirectStandardOutput = true;
            //add in the start info and start the process. 
            openpicture.StartInfo = openpictureStartInfo;
            openpicture.Start();
            openpicture.WaitForExit();
            openpicture.Close();
        }

        private void worldpicprocess2()
        {
            string openpicname = fbdWorldPics.SelectedPath + "\\world2.png\"";
            string args = "-w \"" + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                + "\\My Games\\Terraria\\Worlds\\world2.wld\" -o \"" 
                + fbdWorldPics.SelectedPath + "\\world2.png\"";
            if (ofdWorld2.FileName != "")
            {
                string worldname = ofdWorld2.SafeFileName;
                char[] delimiterChars = { '.' };
                string[] pngname = worldname.Split(delimiterChars);
                string picname = pngname[0];
                args = "-w \"" + ofdWorld2.FileName + "\" -o \"" 
                    + fbdWorldPics.SelectedPath + "\\" + picname + ".png\"";
            }

            Process myProcess = new Process();
            ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ofdMoreTerra.FileName, args);
            myProcessStartInfo.UseShellExecute = false;
            myProcessStartInfo.CreateNoWindow = true;
            myProcess.StartInfo = myProcessStartInfo;
            myProcess.Start();
            myProcess.WaitForExit();
            myProcess.Close();
            Process openpicture = new Process();
            if (ofdWorld2.FileName != "")
            {
                string worldname = ofdWorld2.SafeFileName;
                char[] delimiterChars = { '.' };
                string[] pngname = worldname.Split(delimiterChars);
                string picname = pngname[0];
                openpicname = fbdWorldPics.SelectedPath + "\\" + picname + ".png";
            }

            ProcessStartInfo openpictureStartInfo = new ProcessStartInfo("explorer.exe", openpicname);
            openpictureStartInfo.UseShellExecute = false;
            openpictureStartInfo.CreateNoWindow = true;
            openpictureStartInfo.RedirectStandardOutput = true;
            openpicture.StartInfo = openpictureStartInfo;
            openpicture.Start();
            openpicture.WaitForExit();
            openpicture.Close();
        }

        private void worldpicprocess3()
        {
            string openpicname = fbdWorldPics.SelectedPath + "\\world3.png\"";
            string args = "-w \"" + Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) 
                + "\\My Games\\Terraria\\Worlds\\world3.wld\" -o \"" 
                + fbdWorldPics.SelectedPath + "\\world3.png\"";
            if (ofdWorld3.FileName != "")
            {
                string worldname = ofdWorld3.SafeFileName;
                char[] delimiterChars = { '.' };
                string[] pngname = worldname.Split(delimiterChars);
                string picname = pngname[0];
                args = "-w \"" + ofdWorld3.FileName + "\" -o \"" 
                    + fbdWorldPics.SelectedPath + "\\" + picname + ".png\"";
            }

            Process myProcess = new Process();
            ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(ofdMoreTerra.FileName, args);
            myProcessStartInfo.UseShellExecute = false;
            myProcessStartInfo.CreateNoWindow = true;
            myProcess.StartInfo = myProcessStartInfo;
            myProcess.Start();
            myProcess.WaitForExit();
            myProcess.Close();

            Process openpicture = new Process();
            if (ofdWorld3.FileName != "")
            {
                string worldname = ofdWorld3.SafeFileName;
                char[] delimiterChars = { '.' };
                string[] pngname = worldname.Split(delimiterChars);
                string picname = pngname[0];
                openpicname = fbdWorldPics.SelectedPath + "\\" + picname + ".png";
            }
            ProcessStartInfo openpictureStartInfo = new ProcessStartInfo("explorer.exe", openpicname);
            openpictureStartInfo.UseShellExecute = false;
            openpictureStartInfo.CreateNoWindow = true;
            openpictureStartInfo.RedirectStandardOutput = true;
            openpicture.StartInfo = openpictureStartInfo;
            openpicture.Start();
            openpicture.WaitForExit();
            openpicture.Close();
        }

        private void btnSetWorldPicLocation_Click(object sender, EventArgs e)
        {
            if (fbdWorldPics.ShowDialog() == DialogResult.OK)
            {

            }
        }
        #endregion

        #region settings
        #region Set World
        private void btnWorld1_Click(object sender, EventArgs e)
        {
            ofdWorld1.ShowDialog();
        }

        private void btnWorld2_Click(object sender, EventArgs e)
        {
            ofdWorld2.ShowDialog();
        }

        private void btnWorld3_Click(object sender, EventArgs e)
        {
            ofdWorld3.ShowDialog();
        }
        #endregion

        #region SetConfig
        private void btnConfig1_Click(object sender, EventArgs e)
        {
            ofdConfig1.ShowDialog();
        }

        private void btnConfig2_Click(object sender, EventArgs e)
        {
            ofdConfig2.ShowDialog();
        }

        private void btnConfig3_Click(object sender, EventArgs e)
        {
            ofdConfig3.ShowDialog();
        }
        #endregion

        private void btnSetHistLog_Click(object sender, EventArgs e)
        {
            if (fbdHistlog.ShowDialog() == DialogResult.OK)
            {
                histlog = fbdHistlog.SelectedPath;
            }
        }

        private void btnSetBackupLocation_Click(object sender, EventArgs e)
        {
           fbdBackupLocation.ShowDialog();
        }

        private void btnSetWorldLocation_Click(object sender, EventArgs e)
        {
            if (fbdWorldLocation.ShowDialog() == DialogResult.OK)
            {

            }
        }

        private void btnServerExe_Click(object sender, EventArgs e)
        {
            //set path to server exe. 
            ofdServerExe.ShowDialog();
        }

        #endregion

        #region config checked
        private void cbkConfig1_CheckedChanged(object sender, EventArgs e)
        {
            if (cbkConfig1.Checked)
            {
                nudPlayers1.Enabled = false;
                nudPort1.Enabled = false;
                btnWorld1.Enabled = false;
            }
            else
            {
                nudPlayers1.Enabled = true;
                nudPort1.Enabled = true;
                btnWorld1.Enabled = true;
            }
        }

        private void cbkConfig2_CheckedChanged(object sender, EventArgs e)
        {
            if (cbkConfig2.Checked)
            {
                nudPlayers2.Enabled = false;
                nudPort2.Enabled = false;
                btnWorld2.Enabled = false;
            }
            else
            {
                nudPlayers2.Enabled = true;
                nudPort2.Enabled = true;
                btnWorld2.Enabled = true;
            }
        }

        private void cbkConfig3_CheckedChanged(object sender, EventArgs e)
        {
            if (cbkConfig3.Checked)
            {
                nudPlayers3.Enabled = false;
                nudPort3.Enabled = false;
                btnWorld3.Enabled = false;
            }
            else
            {
                nudPlayers3.Enabled = true;
                nudPort3.Enabled = true;
                btnWorld3.Enabled = true;
            }
        }

        private void cbkConfig4_CheckedChanged(object sender, EventArgs e)
        {
            if (cbkConfig4.Checked)
            {
                nudPlayers4.Enabled = false;
                nudPort4.Enabled = false;
                btnWorld4.Enabled = false;
            }
            else
            {
                nudPlayers4.Enabled = true;
                nudPort4.Enabled = true;
                btnWorld4.Enabled = true;
            }
        }
        #endregion

        private void CheckKeys(object sender, System.Windows.Forms.KeyPressEventArgs e)
        {
            //this fucntion checks to see if the enter button was hit on txtServerEntry if it was
            //it sends the server that is selected in the cboServerNumb. 
            if (e.KeyChar == (char)13)
            {
                if (cboServerNumb.Text == "Server 1")
                {
                    if (cboCMDType.SelectedIndex == 0)
                    {
                        StreamWriterServer1.WriteLine("say " + txtServerEntry.Text);
                    }
                    else
                    {
                        StreamWriterServer1.WriteLine(txtServerEntry.Text);
                    }
                }
                if (cboServerNumb.Text == "Server 2")
                {
                    if (cboCMDType.SelectedIndex == 0)
                    {
                        StreamWriterServer2.WriteLine("say " + txtServerEntry.Text);
                    }
                    else
                    {
                        StreamWriterServer2.WriteLine(txtServerEntry.Text);
                    }
                }
                if (cboServerNumb.Text == "Server 3")
                {
                    if (cboCMDType.SelectedIndex == 0)
                    {
                        StreamWriterServer3.WriteLine("say " + txtServerEntry.Text);
                    }
                    else
                    {
                        StreamWriterServer3.WriteLine(txtServerEntry.Text);
                    }
                }
                txtServerEntry.Text = "";
            }
        }

        private void btnBanIP_Click(object sender, EventArgs e)
        {
            //Simply this: opens the banlist file, writes the ip in the text box and then closes it. 
            TextWriter tw = 
                File.AppendText(
                "C:\\Program Files (x86)\\Steam\\steamapps\\common\\terraria\\banlist.txt");
            tw.WriteLine(txtBanIP.Text);
            tw.Close();
            //Add it to the history box, log it and scroll history box down. 
            AddHistBoxItem("[" + DateTime.Now + "] " + txtBanIP.Text + " has been banned.");
            System.IO.File.AppendAllText(histlog, "[" + DateTime.Now + "] " 
                + txtBanIP.Text + " has been banned." + "\n");
            lstscrolldown();
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            lstConnections.Items.Clear();
            if (btnServer1Stop.Enabled)
                StreamWriterServer1.WriteLine("playing");
            if (btnServer2Stop.Enabled)
                StreamWriterServer2.WriteLine("playing");
            if (btnServer3Stop.Enabled)
                StreamWriterServer3.WriteLine("playing");
        }

        private void btnLicense_Click(object sender, EventArgs e)
        {
            //This Fulfils the second clause of the BSD-Brune License.
            StringBuilder LicenseBuilder = new StringBuilder();
            LicenseBuilder.Append(
                "\n*BSD-Brune License");
            LicenseBuilder.Append(
                "\n* Copywrite (C) 2012, Michael J Brune <admin@mjbrune.org>");
            LicenseBuilder.Append(
                "\n* All rights reserved.");
            LicenseBuilder.Append(
                "\n* Redistribution and use in source and binary forms, with or without");
            LicenseBuilder.Append(
                "\n* modification, are permitted provided that the following conditions are met:");
            LicenseBuilder.Append(
                "\n* ");
            LicenseBuilder.Append(
                "\n* 1. Redistributions of source code must retain the above copyright");
            LicenseBuilder.Append(
                "\n* notice, this list of conditions and the following disclaimer.");
            LicenseBuilder.Append(
                "\n* ");
            LicenseBuilder.Append(
                "\n* 2. Redistributions in binary form must reproduce the above copyright");
            LicenseBuilder.Append(
                "\n* notice, this list of conditions and the following disclaimer in the");
            LicenseBuilder.Append(
                "\n* documentation and/or other materials provided with the distribution.");
            LicenseBuilder.Append(
                "\n* ");
            LicenseBuilder.Append(
                "\n* 3. All contributors must keep their code clean, commented and keep the");
            LicenseBuilder.Append(
                "\n* changelog section up to date.");
            LicenseBuilder.Append(
                "\n* ");
            LicenseBuilder.Append(
                "\n* THIS SOFTWARE IS PROVIDED BY Michael J Brune ''AS IS'' AND ANY");
            LicenseBuilder.Append(
                "\n* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE");
            LicenseBuilder.Append(
                "\n* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A");
            LicenseBuilder.Append(
                "\n* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Michael J Brune");
            LicenseBuilder.Append(
                "\n* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,");
            LicenseBuilder.Append(
                "\n* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,");
            LicenseBuilder.Append(
                "\n* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,");
            LicenseBuilder.Append(
                "\n* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON");
            LicenseBuilder.Append(
                "\n* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,");
            LicenseBuilder.Append(
                "\n* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY");
            LicenseBuilder.Append(
                "\n* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY");
            LicenseBuilder.Append(
                "\n* OF SUCH DAMAGE.");
            MessageBox.Show(LicenseBuilder.ToString(), "BSD-Brune License");
        }

    }
}