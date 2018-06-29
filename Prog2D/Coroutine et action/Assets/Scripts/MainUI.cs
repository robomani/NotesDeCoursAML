using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainUI : MonoBehaviour
{
    public Slider m_LifeBar;

    private void Start()
    {
        if (GameManager.Instance.m_Player != null)
        {
            GameManager.Instance.m_Player.m_HurtAction += SetLifeValue;
        } 
    }


    private void SetLifeValue(int a_Value)
    {
        m_LifeBar.value = a_Value;
    }

    private void OnDestroy()
    {
        if (GameManager.Instance.m_Player != null)
        {
            GameManager.Instance.m_Player.m_HurtAction -= SetLifeValue;
        }
    }
}
