﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelManager : MonoBehaviour
{
    public GameObject m_LoadingScreen;
    private static LevelManager m_Instance;
    public static LevelManager Instance
    {
        get { return m_Instance; }
    }

    private void Awake()
    {
        //Destroy the object if it is not the first
        if (m_Instance != null)
        {
            Debug.Log("Already exist kill self");
            Destroy(gameObject);
        }
        //else assign the first instance to show that the singleton exist and let it be called
        else
        {
            Debug.Log("First one king of the hill");
            m_Instance = this;
            DontDestroyOnLoad(gameObject);
        }
        m_LoadingScreen.SetActive(false);
    }

    private void StartLoading()
    {
        m_LoadingScreen.SetActive(true);
        //Play Animation
    }

    private void OnLoadingDone(Scene i_Scene, LoadSceneMode i_Mode)
    {
        //we remove the function to the action/event list
        SceneManager.sceneLoaded -= OnLoadingDone;
        //Stop Animation
        //m_LoadingScreen.SetActive(false);
        //m_IsLoadingDone = true
    }

    public void ChangeLevel(string i_Scene)
    {
        StartLoading();
        SceneManager.LoadScene(i_Scene);
        //StartCoroutine qui attend 3 secondes et m_IsLoadingDone == True
        //Action/Event that trigger automaticlly the given function
        //we add the function to the action/event list
        SceneManager.sceneLoaded += OnLoadingDone;
    }
}
