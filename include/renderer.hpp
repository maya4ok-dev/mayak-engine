// File: Renderer.h

#pragma once

namespace mayak::gfx {
    /// \brief Initializes the renderer by creating a window and renderer and by loading all textures
    ///
    /// \param name The name of the window
    /// \return true if the renderer was initialized successfully, false otherwise
    bool init(const char *name);

    /// \brief Render all objects in the current DIM
    ///
    /// This function will iterate over all objects in the current DIM, and render
    /// them to the screen. This will first clear the screen with a white color,
    /// and then render each object at its position with its size.
    ///
    /// If the texture for an object is not found, an error message will be logged
    /// and the function will return.
    ///
    /// If an error occurs while rendering an object, a fatal error message will
    /// be logged and the function will return.
    ///
    /// After all objects have been rendered, the rendered screen will be presented
    /// to the user.
    void render();

    /// \brief Clean up the renderer and window
    /// 
    /// This function should be called when the program is exiting. It will
    /// free all resources allocated by the renderer, including the window,
    /// renderer, and textures.
    void cleanup();

    /// \brief Checks if the renderer has been initialized
    ///
    /// \returns true if the renderer has been initialized, false otherwise
    ///
    /// This function checks if the window and renderer have been initialized.
    /// It is used in the main loop to prevent rendering if the window or
    /// renderer has not been initialized yet.
    bool isInitialized() noexcept;

    /// \brief Returns the current state of VSync
    ///
    /// \return true if VSync is enabled, false otherwise
    bool getVSync() noexcept;

    /// \brief Set whether the renderer should use VSync or not
    ///
    /// \param value true to enable VSync, false to disable it
    ///
    /// VSync, or vertical sync, is a feature that synchronizes the frame
    /// rate with the monitor's refresh rate. This can help prevent tearing,
    /// but can also cause the frame rate to drop.
    void setVSync(bool state);
};
