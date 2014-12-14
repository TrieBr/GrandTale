namespace mapEditor
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.mainMenu1 = new System.Windows.Forms.MainMenu(this.components);
            this.menuItem1 = new System.Windows.Forms.MenuItem();
            this.menuItem2 = new System.Windows.Forms.MenuItem();
            this.menuItem3 = new System.Windows.Forms.MenuItem();
            this.menuItem4 = new System.Windows.Forms.MenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.placementTabs = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.grpTileSelect = new System.Windows.Forms.GroupBox();
            this.pnlTilePreview = new System.Windows.Forms.PictureBox();
            this.cmbTileSelection = new System.Windows.Forms.ComboBox();
            this.lblTilePrompt = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnAddLayer = new System.Windows.Forms.Button();
            this.cmbLayerSelection = new System.Windows.Forms.ComboBox();
            this.lblLayerPrompt = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.panel2 = new System.Windows.Forms.Panel();
            this.pnlMapPreview = new System.Windows.Forms.PictureBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.txtMapWidth = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.txtMapHeight = new System.Windows.Forms.ToolStripTextBox();
            this.assetFolderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.placementTabs.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.grpTileSelect.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlTilePreview)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlMapPreview)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainMenu1
            // 
            this.mainMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem1,
            this.menuItem3});
            // 
            // menuItem1
            // 
            this.menuItem1.Index = 0;
            this.menuItem1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem2});
            this.menuItem1.Text = "File";
            // 
            // menuItem2
            // 
            this.menuItem2.Index = 0;
            this.menuItem2.Text = "Exit";
            // 
            // menuItem3
            // 
            this.menuItem3.Index = 1;
            this.menuItem3.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
            this.menuItem4});
            this.menuItem3.Text = "Options";
            // 
            // menuItem4
            // 
            this.menuItem4.Index = 0;
            this.menuItem4.Text = "Graphics Asset Path";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.placementTabs);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.panel2);
            this.splitContainer1.Size = new System.Drawing.Size(1045, 558);
            this.splitContainer1.SplitterDistance = 348;
            this.splitContainer1.TabIndex = 0;
            // 
            // placementTabs
            // 
            this.placementTabs.Controls.Add(this.tabPage1);
            this.placementTabs.Controls.Add(this.tabPage2);
            this.placementTabs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.placementTabs.Location = new System.Drawing.Point(0, 0);
            this.placementTabs.Name = "placementTabs";
            this.placementTabs.SelectedIndex = 0;
            this.placementTabs.Size = new System.Drawing.Size(348, 558);
            this.placementTabs.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.grpTileSelect);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(340, 532);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Tiles";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // grpTileSelect
            // 
            this.grpTileSelect.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.grpTileSelect.Controls.Add(this.pnlTilePreview);
            this.grpTileSelect.Controls.Add(this.cmbTileSelection);
            this.grpTileSelect.Controls.Add(this.lblTilePrompt);
            this.grpTileSelect.Location = new System.Drawing.Point(6, 57);
            this.grpTileSelect.Name = "grpTileSelect";
            this.grpTileSelect.Size = new System.Drawing.Size(331, 467);
            this.grpTileSelect.TabIndex = 1;
            this.grpTileSelect.TabStop = false;
            this.grpTileSelect.Text = "Tile";
            // 
            // pnlTilePreview
            // 
            this.pnlTilePreview.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlTilePreview.BackColor = System.Drawing.Color.DarkGray;
            this.pnlTilePreview.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.pnlTilePreview.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pnlTilePreview.Location = new System.Drawing.Point(6, 19);
            this.pnlTilePreview.Name = "pnlTilePreview";
            this.pnlTilePreview.Size = new System.Drawing.Size(322, 400);
            this.pnlTilePreview.TabIndex = 3;
            this.pnlTilePreview.TabStop = false;
            this.pnlTilePreview.Click += new System.EventHandler(this.pnlTilePreview_Click);
            this.pnlTilePreview.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnlTilePreview_MouseDown);
            // 
            // cmbTileSelection
            // 
            this.cmbTileSelection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbTileSelection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbTileSelection.FormattingEnabled = true;
            this.cmbTileSelection.Location = new System.Drawing.Point(39, 437);
            this.cmbTileSelection.Name = "cmbTileSelection";
            this.cmbTileSelection.Size = new System.Drawing.Size(286, 21);
            this.cmbTileSelection.TabIndex = 2;
            this.cmbTileSelection.SelectedIndexChanged += new System.EventHandler(this.cmbTileSelection_SelectedIndexChanged);
            // 
            // lblTilePrompt
            // 
            this.lblTilePrompt.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblTilePrompt.AutoSize = true;
            this.lblTilePrompt.Location = new System.Drawing.Point(6, 440);
            this.lblTilePrompt.Name = "lblTilePrompt";
            this.lblTilePrompt.Size = new System.Drawing.Size(27, 13);
            this.lblTilePrompt.TabIndex = 1;
            this.lblTilePrompt.Text = "Tile:";
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.btnAddLayer);
            this.groupBox1.Controls.Add(this.cmbLayerSelection);
            this.groupBox1.Controls.Add(this.lblLayerPrompt);
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(334, 48);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Layer Info";
            // 
            // btnAddLayer
            // 
            this.btnAddLayer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnAddLayer.Location = new System.Drawing.Point(253, 11);
            this.btnAddLayer.Name = "btnAddLayer";
            this.btnAddLayer.Size = new System.Drawing.Size(75, 23);
            this.btnAddLayer.TabIndex = 2;
            this.btnAddLayer.Text = "Add Layer";
            this.btnAddLayer.UseVisualStyleBackColor = true;
            // 
            // cmbLayerSelection
            // 
            this.cmbLayerSelection.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbLayerSelection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbLayerSelection.FormattingEnabled = true;
            this.cmbLayerSelection.Location = new System.Drawing.Point(48, 13);
            this.cmbLayerSelection.Name = "cmbLayerSelection";
            this.cmbLayerSelection.Size = new System.Drawing.Size(199, 21);
            this.cmbLayerSelection.TabIndex = 1;
            // 
            // lblLayerPrompt
            // 
            this.lblLayerPrompt.AutoSize = true;
            this.lblLayerPrompt.Location = new System.Drawing.Point(6, 16);
            this.lblLayerPrompt.Name = "lblLayerPrompt";
            this.lblLayerPrompt.Size = new System.Drawing.Size(36, 13);
            this.lblLayerPrompt.TabIndex = 0;
            this.lblLayerPrompt.Text = "Layer:";
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(340, 532);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.SystemColors.Control;
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Controls.Add(this.pnlMapPreview);
            this.panel2.Controls.Add(this.toolStrip1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(693, 558);
            this.panel2.TabIndex = 0;
            // 
            // pnlMapPreview
            // 
            this.pnlMapPreview.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.pnlMapPreview.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlMapPreview.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlMapPreview.Location = new System.Drawing.Point(0, 25);
            this.pnlMapPreview.Name = "pnlMapPreview";
            this.pnlMapPreview.Size = new System.Drawing.Size(689, 529);
            this.pnlMapPreview.TabIndex = 1;
            this.pnlMapPreview.TabStop = false;
            this.pnlMapPreview.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnlMapPreview_MouseDown);
            this.pnlMapPreview.MouseHover += new System.EventHandler(this.pnlMapPreview_MouseHover);
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton2,
            this.toolStripButton1,
            this.toolStripLabel1,
            this.txtMapWidth,
            this.toolStripLabel2,
            this.txtMapHeight});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(689, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton2.Text = "toolStripButton2";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.Text = "Toggle Grid";
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(69, 22);
            this.toolStripLabel1.Text = "Map Width:";
            // 
            // txtMapWidth
            // 
            this.txtMapWidth.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtMapWidth.Name = "txtMapWidth";
            this.txtMapWidth.Size = new System.Drawing.Size(100, 25);
            this.txtMapWidth.TextChanged += new System.EventHandler(this.txtMapWidth_TextChanged);
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(73, 22);
            this.toolStripLabel2.Text = "Map Height:";
            // 
            // txtMapHeight
            // 
            this.txtMapHeight.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtMapHeight.Name = "txtMapHeight";
            this.txtMapHeight.Size = new System.Drawing.Size(100, 25);
            this.txtMapHeight.TextChanged += new System.EventHandler(this.txtMapWidth_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1045, 558);
            this.Controls.Add(this.splitContainer1);
            this.Menu = this.mainMenu1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.placementTabs.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.grpTileSelect.ResumeLayout(false);
            this.grpTileSelect.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlTilePreview)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pnlMapPreview)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.MainMenu mainMenu1;
        private System.Windows.Forms.MenuItem menuItem1;
        private System.Windows.Forms.MenuItem menuItem2;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TabControl placementTabs;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnAddLayer;
        private System.Windows.Forms.ComboBox cmbLayerSelection;
        private System.Windows.Forms.Label lblLayerPrompt;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox grpTileSelect;
        private System.Windows.Forms.ComboBox cmbTileSelection;
        private System.Windows.Forms.Label lblTilePrompt;
        private System.Windows.Forms.MenuItem menuItem3;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.MenuItem menuItem4;
        private System.Windows.Forms.FolderBrowserDialog assetFolderBrowser;
        private System.Windows.Forms.PictureBox pnlTilePreview;
        private System.Windows.Forms.PictureBox pnlMapPreview;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripTextBox txtMapWidth;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripTextBox txtMapHeight;
    }
}

